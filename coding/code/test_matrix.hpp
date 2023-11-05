#pragma once

#include <set>
#include <ostream>
#include <Eigen/Core>

struct test_matrix_info
{
    using test_matrix_t = Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic>;

    test_matrix_t matrix;
    std::set<size_t> pos_test_symbols;

    friend std::ostream &operator<<(std::ostream &out, const test_matrix_info &info);
};
