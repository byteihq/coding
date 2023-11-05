#pragma once

#include <Eigen/Core>
#include <vec.hpp>

class utils final
{
public:
    template <typename It>
    static size_t weight(It begin, It end)
    {
        size_t w = 0;
        for (auto it = begin; it != end; ++it)
        {
            if (*it != 0)
                ++w;
        }

        return w;
    }

    static Eigen::Vector<typename vec::value_type, Eigen::Dynamic> vec_to_eigen_vec(vec &data)
    {
        return Eigen::Map<Eigen::Vector<typename vec::value_type, Eigen::Dynamic>>(data.data(), data.size());
    }

    static vec gen_random_vec(size_t len, size_t mod);

    static size_t get_inv(size_t v, size_t q);
    static size_t mod(int64_t v, size_t mod);

    static void make_k_mistakes(vec &data, size_t k, size_t q);
};
