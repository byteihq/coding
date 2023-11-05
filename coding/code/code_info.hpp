#pragma once

#include <ostream>

struct code_info
{
    size_t q; // notation
    size_t m; // number of test symbols
    size_t n; // len of encoded msg
    size_t k; // len of plain msg
    size_t d; //
    size_t t; //
    float r; // code speed


    friend std::ostream &operator<<(std::ostream &out, const code_info &info);
};
