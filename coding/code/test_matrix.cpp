#include "test_matrix.hpp"
#include <sstream>

std::ostream &operator<<(std::ostream &out, const test_matrix_info &info)
{
    std::stringstream test_matrix;
    test_matrix << info.matrix;
    out << "Test matrix:";
    std::string test_matrix_line;
    for (; std::getline(test_matrix, test_matrix_line); out << "\n\t" << test_matrix_line);

    out << "\nPos test symbols:\n\t";
    for (const auto &pos : info.pos_test_symbols)
        out << pos << ' ';
    return out;
}
