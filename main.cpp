#include <iostream>
#include <hamming.hpp>
#include <utils.hpp>

int main()
{
    constexpr auto len = 18;
    constexpr auto k = 10;
    constexpr auto q = 3;
    auto vec = utils::gen_random_vec(len, q);
    auto code = hamming::encode(vec, k, q);
    std::cout << code.info.cp << '\n' << code.info.tm << '\n';
    std::cout << "Plain data:\n" << code.info.plain_data << std::endl;
    std::cout << "Encoded data:\n" << code.info.encoded_data << std::endl;
    for (size_t i = 0; i < code.info.encoded_data.data.size(); ++i)
    {
        utils::make_k_mistakes(code.info.encoded_data.data[i], 1, q);
    }
    std::cout << "Encoded blocks with 1 mistake\n" << code.info.encoded_data << std::endl;

    auto dec = hamming::decode(code);
    for (size_t i = 0; i < dec.errors.size(); ++i)
    {
        std::cout << "Syndrom[" << i << "]:\t" << dec.errors[i].syndrom << "\nDecoded:\t" << dec.info.plain_data.data[i] << std::endl;
    }
    return 0;
}
