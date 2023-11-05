#include "hamming.hpp"
#include <utils.hpp>

#include <cmath>
#include <numeric>

code_info hamming::get_code_info_by_q_k(size_t q, size_t k)
{
    size_t m = 1;
    for (; k > (std::pow(q, m) - 1) / (q - 1) - m; ++m)
        ;
    size_t n = static_cast<size_t>((std::pow(q, m) - 1) / (q - 1));
    k = n - m;
    return {q, m, n, k, 3, 1, static_cast<float>(k) / n};
}

code_info hamming::get_code_info_by_q_n(size_t q, size_t n)
{
    size_t m = 1;
    for (; n > (std::pow(q, m) - 1) / (q - 1); ++m)
        ;
    n = (std::pow(q, m) - 1) / (q - 1);
    auto k = n - m;
    return {q, m, n, k, 3, 1, static_cast<float>(k) / n};
}

test_matrix_info hamming::get_test_matrix_info(const code_info &params)
{
    test_matrix_info::test_matrix_t test_matrix;
    test_matrix.conservativeResize(params.m, params.n);

    std::set<size_t> pos_test_symbols = {0};

    vec cur_col(params.m, 0);
    cur_col.back() = 1;
    test_matrix.col(0) = utils::vec_to_eigen_vec(cur_col);
    std::fill(cur_col.begin(), cur_col.end(), 0);

    size_t lvl = params.m - 2;
    size_t i = 1;
    while (i < params.n)
    {
        cur_col[lvl] = 1;
        pos_test_symbols.insert(i);
        auto it = std::prev(cur_col.end());
        for (;;)
        {
            test_matrix.col(i++) = utils::vec_to_eigen_vec(cur_col);
            if (*it + 1 < params.q)
            {
                ++(*it);
            }
            else
            {
                bool overflow = true;
                auto tmp_it = std::prev(it);
                while (std::distance(cur_col.begin(), tmp_it) > lvl)
                {
                    if (*tmp_it + 1 < params.q)
                    {
                        ++(*tmp_it);
                        overflow = false;
                        break;
                    }
                    tmp_it = std::prev(tmp_it);
                }
                if (overflow)
                {
                    --lvl;
                    std::fill(cur_col.begin(), cur_col.end(), 0);
                    break;
                }

                std::fill(std::next(tmp_it), cur_col.end(), 0);
                it = std::prev(cur_col.end());
            }
        }
    }

    return {test_matrix, pos_test_symbols};
}

hamming::encoded_msg hamming::encode(const vec &msg, size_t q)
{
    return encode(msg, get_code_info_by_q_k(q, msg.size()));
}

hamming::encoded_msg hamming::encode(const vec &msg, size_t k, size_t q)
{
    return encode(msg, get_code_info_by_q_k(q, k));
}

hamming::encoded_msg hamming::encode(const vec &msg, const code_info &params)
{
    auto tm = get_test_matrix_info(params);

    blocks plain_blocks;
    blocks encoded_blocks;
    size_t i = 0;
    while (i < msg.size())
    {
        auto step = std::min(params.k, msg.size() - i);
        plain_blocks.data.push_back({msg.begin() + i, msg.begin() + i + step});
        encoded_blocks.data.push_back(encode_one(plain_blocks.data.back(), params, tm));
        i += step;
    }

    return {msg_info{tm, params, plain_blocks, encoded_blocks}};
}

vec hamming::encode_one(const vec &msg, const code_info &params, const test_matrix_info &tm)
{
    vec encoded_msg(params.n, 0);
    size_t j = 0;
    for (size_t i = 0; i < encoded_msg.size(); ++i)
    {
        if (!tm.pos_test_symbols.contains(i))
        {
            if (j < msg.size())
                encoded_msg[i] = msg[j++];
            else
                break;
        }
    }

    for (auto it = tm.pos_test_symbols.rbegin(); it != tm.pos_test_symbols.rend(); ++it)
    {
        auto row = tm.matrix.row(std::distance(tm.pos_test_symbols.rbegin(), it));
        auto check_sum = 0;
        for (size_t i = 0; i < row.size(); ++i)
        {
            check_sum += row[i] * encoded_msg[i];
            check_sum %= params.q;
        }
        encoded_msg[*it] = (params.q - check_sum) % params.q;
    }

    return encoded_msg;
}

hamming::decoded_msg hamming::decode(const vec &msg, size_t q)
{
    return decode(msg, get_code_info_by_q_n(q, msg.size()));
}

hamming::decoded_msg hamming::decode(const vec &msg, size_t k, size_t q)
{
    return decode(msg, get_code_info_by_q_k(q, k));
}

hamming::decoded_msg hamming::decode(const vec &msg, const code_info &params)
{
    auto tm = get_test_matrix_info(params);
    return decode({msg_info{tm, params, blocks::container{msg}, {}}});
}

hamming::decoded_msg hamming::decode(const encoded_msg &msg)
{
    decoded_msg dm;

    for (size_t i = 0; i < msg.info.encoded_data.data.size(); ++i)
    {
        auto [decoded_vec, err] = decode_one(msg.info.encoded_data.data[i], msg.info.cp, msg.info.tm);
        dm.info.plain_data.data.push_back(decoded_vec);
        dm.errors.push_back(err);
    }
    dm.info = msg.info;

    return dm;
}

std::pair<vec, hamming::decoded_msg::error> hamming::decode_one(const vec &msg, const code_info &params, const test_matrix_info &tm)
{
    vec syndrom(tm.matrix.rows(), 0);

    vec _msg;
    std::copy(msg.begin(), msg.end(), std::back_inserter(_msg));
    _msg.resize(params.n, 0);

    for (size_t i = 0; i < syndrom.size(); ++i)
    {
        size_t tmp = 0;
        auto row = tm.matrix.row(i);
        for (size_t j = 0; j < row.size(); ++j)
        {
            tmp += row[j] * _msg[j];
            tmp %= params.q;
        }
        syndrom[i] = tmp;
    }

    auto err = decode_by_syndrom(syndrom, params);
    _msg[err.pos] -= err.value;
    _msg[err.pos] = utils::mod(_msg[err.pos], params.q);

    return {_msg, err};
}

hamming::decoded_msg::error hamming::decode_by_syndrom(const vec &syndrom, const code_info &params)
{
    auto pos_first_not_0 = std::find_if(syndrom.begin(), syndrom.end(), [](vec::value_type value)
                                        { return value != 0; });
    if (pos_first_not_0 == syndrom.end())
        return {syndrom, 0, 0};

    auto err = utils::get_inv(*pos_first_not_0, params.q);
    size_t pos = 0;
    size_t lim = syndrom.size() - std::distance(syndrom.begin(), pos_first_not_0) - 1;
    uint64_t v = 1;
    for (size_t i = 0; i < lim; pos += v, v *= params.q, ++i)
        ;
    v = 1;
    for (size_t i = 0; i < lim; pos += ((err * syndrom[syndrom.size() - i - 1]) % params.q) * v, v *= params.q, ++i)
        ;

    return {syndrom, err, pos};
}
