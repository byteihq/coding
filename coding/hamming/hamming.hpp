#pragma once

#include <msg_info.hpp>
#include <vec.hpp>

class hamming final
{
public:
    struct encoded_msg
    {
        msg_info info;
    };

    struct decoded_msg
    {
        msg_info info;
        struct error
        {
            vec syndrom;
            size_t value;
            size_t pos;
        };

        std::vector<error> errors;
    };

private:
    static code_info get_code_info_by_q_k(size_t q, size_t k);
    static code_info get_code_info_by_q_n(size_t q, size_t n);
    static test_matrix_info get_test_matrix_info(const code_info &params);
    static vec encode_one(const vec &msg, const code_info &params, const test_matrix_info &tm);
    static std::pair<vec, decoded_msg::error> decode_one(const vec &msg, const code_info &params, const test_matrix_info &tm);

public:
    static encoded_msg encode(const vec &msg, size_t q);
    static encoded_msg encode(const vec &msg, size_t k, size_t q);
    static encoded_msg encode(const vec &msg, const code_info &params);

    static decoded_msg decode(const vec &msg, size_t q);
    static decoded_msg decode(const vec &msg, size_t k, size_t q);
    static decoded_msg decode(const vec &msg, const code_info &params);
    static decoded_msg decode(const encoded_msg &msg);
    static decoded_msg::error decode_by_syndrom(const vec &syndrom, const code_info &params);
};
