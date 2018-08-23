#include <botan/mode_pad.h>
#include "padding.hpp"

void crypto::padding::add_PKCS7_padding(std::vector<uint8_t> &data, size_t block_size) {
    size_t bytes_to_add = block_size - data.size() % block_size;

    std::vector<uint8_t> bytes(bytes_to_add, bytes_to_add);
    data.insert(data.end(), bytes.begin(), bytes.end());
}
