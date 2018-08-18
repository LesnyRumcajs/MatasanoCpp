#ifndef MATASANOCPP_PADDING_HPP
#define MATASANOCPP_PADDING_HPP

#include <cstdint>
#include <vector>
#include <cstddef>

namespace crypto::padding {
    void add_PKCS7_padding(std::vector<uint8_t> &data, size_t block_size);
}

#endif //MATASANOCPP_PADDING_HPP
