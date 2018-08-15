#include "xor.hpp"

#include <botan-2/botan/hex.h>
#include <stdexcept>

std::string matasano::xor_hex(const std::string &first, const std::string &second) {
    auto first_decoded = Botan::hex_decode(first);
    auto second_decoded = Botan::hex_decode(second);

    return Botan::hex_encode(xor_container(first_decoded, second_decoded), false);
}
