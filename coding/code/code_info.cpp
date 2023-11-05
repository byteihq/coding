#include "code_info.hpp"

std::ostream &operator<<(std::ostream &out, const code_info &info)
{
    out << "Code params:"
    << "\n\tq: " << info.q
    << "\n\tm: " << info.m
    << "\n\tn: " << info.n
    << "\n\tk: " << info.k
    << "\n\td: " << info.d
    << "\n\tt: " << info.t
    << "\n\tr: " << info.r;

    return out;
}
