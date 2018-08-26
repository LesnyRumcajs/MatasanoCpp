#include <stdexcept>
#include "aes_key_generator.hpp"

#include <botan/auto_rng.h>

std::vector<uint8_t> AESKeyGenerator::generate(size_t key_size) const {
    validate_key_size(key_size);
    Botan::AutoSeeded_RNG rng;

    std::vector<uint8_t> key(key_size);
    rng.randomize(key.data(), key_size);
    return key;
}

void AESKeyGenerator::validate_key_size(size_t key_size) const {
    if (key_size != BLOCK_SIZE && key_size != BLOCK_SIZE * 2 && key_size != BLOCK_SIZE * 3) {
        throw std::invalid_argument("Invalid key length for AES key");
    }
}
