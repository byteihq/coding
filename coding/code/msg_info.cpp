#include "msg_info.hpp"

std::ostream &operator<<(std::ostream &out, const blocks &b)
{
    bool first = true;
    for (size_t i = 0; i < b.data.size(); ++i)
    {
        if (!first)
            out << '\n';
        out << "Block[" << i << "]:\t" << b.data[i];
        first = false;
    }

    return out;
}
