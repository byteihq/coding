#include "utils.hpp"
#include <random>
#include <algorithm>
#include <array>
#include <fmt/core.h>

vec utils::gen_random_vec(size_t len, size_t mod)
{
    if (mod == 0)
        return {};

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dst(0, mod - 1);
    vec res(len , 0);
    std::generate(res.begin(), res.end(), [&rng, &dst](){ return dst(rng); });

    return res;
}

size_t utils::get_inv(size_t v, size_t q)
{
    auto mod = q;
    v %= mod;
    if (v == 0)
        throw std::runtime_error(fmt::format("there is no inverse to {} mod {}", v, q));
    std::array<int, 2> l_1 = {1, 0};
    std::array<int, 2> l_2 = {0, 1};

    while (v > 1)
    {
        size_t k = 1;
        for(; v * (k + 1) < q; ++k);
        l_1[0] -= l_2[0] * k;
        l_1[1] -= l_2[1] * k;
        std::swap(l_1, l_2);
        v = std::exchange(q, v) - v * k;
    }

    if (v == 0)
        throw std::runtime_error(fmt::format("there is no inverse to {} mod {}", v, q));

    return utils::mod(l_2[1], mod);
}

size_t utils::mod(int64_t value, size_t mod)
{
    for(; value < 0; value += mod);
    return value % mod;
}

void utils::make_k_mistakes(vec &data, size_t k, size_t q)
{
    if (q < 2)
        return;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dst_pos(0, data.size() - 1);
    std::uniform_int_distribution<size_t> dst_v(0, q - 1);

    for (size_t i = 0; i < k; ++i)
    {
        auto pos = dst_pos(rng);
        auto prev_v = data[pos];
        auto new_v = 0;
        do
        {
            new_v = dst_v(rng);
        } while (prev_v == new_v);
        data[pos] = new_v;
    }
}
