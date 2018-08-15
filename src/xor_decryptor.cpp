#include <botan/hex.h>
#include <map>
#include <iostream>
#include "xor_decryptor.hpp"
#include "text_evaluator.hpp"

std::string XorDecryptor::decrypt_hex(const std::string &hex_ciphertext) const {
    auto binary = Botan::hex_decode(hex_ciphertext);
    return decrypt(binary);
}

std::string XorDecryptor::decrypt(const std::vector<uint8_t> &ciphertext) const {
    int max_score = -1;
    std::string result;

    TextEvaluator evaluator;
    for (uint8_t key = 0x00; key <= 0xFE; ++key) {
        std::string candidate;
        for (const auto ch : ciphertext) {
            candidate += static_cast<char>(ch ^ key);
        }

        auto score = evaluator.score(candidate);
        if (score > max_score) {
            max_score = score;
            result = candidate;
        }
    }

    return result;
}
