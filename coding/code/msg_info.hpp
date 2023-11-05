#pragma once

#include "code_info.hpp"
#include "test_matrix.hpp"
#include <vec.hpp>
#include <vector>
#include <ostream>

struct blocks
{
    using container = std::vector<vec>;
    container data;

    friend std::ostream &operator<<(std::ostream &out, const blocks &b);
};

struct msg_info
{
    test_matrix_info tm;
    code_info cp;

    blocks plain_data;
    blocks encoded_data;
};
