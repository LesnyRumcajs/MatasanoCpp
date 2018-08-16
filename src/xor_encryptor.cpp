#include <stdexcept>
#include <botan/hex.h>
#include "xor_encryptor.hpp"
#include "repeating_key.hpp"

XorEncryptor::XorEncryptor(const std::string &key) : m_key(key.begin(), key.end()) {
    if (key.empty()) {
        throw std::invalid_argument("encryption key cannot be empty!");
    }
}

std::string XorEncryptor::encrypt_hex(const std::string &plaintext) const {
    RepeatingKey repeatingKey(m_key);

    std::vector<uint8_t> ciphertext;

    for (const auto ch : plaintext) {
        ciphertext.emplace_back(static_cast<uint8_t >(ch) ^ repeatingKey.next());
    }

    return Botan::hex_encode(ciphertext, false);
}
