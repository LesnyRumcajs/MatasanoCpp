#include <stdexcept>
#include <botan/hex.h>
#include "xor_encryptor.hpp"
#include "repeating_key.hpp"

XorEncryptor::XorEncryptor(const std::string &key) : m_key(key.begin(), key.end()) {
    if (key.empty()) {
        throw std::invalid_argument("encryption key cannot be empty!");
    }
}

std::vector<uint8_t> XorEncryptor::encrypt(const std::string &plaintext) const {
    return crypt({plaintext.begin(), plaintext.end()});
}

std::string XorEncryptor::decrypt(const std::vector<uint8_t> &ciphertext) const {
    auto result = crypt(ciphertext);
    return {result.begin(), result.end()};
}

std::vector<uint8_t> XorEncryptor::crypt(const std::vector<uint8_t> &data) const {
    RepeatingKey repeatingKey(m_key);

    std::vector<uint8_t> result;

    for (const auto ch : data) {
        result.emplace_back(static_cast<uint8_t >(ch) ^ repeatingKey.next());
    }

    return result;
}
