#include <botan/hex.h>
#include <map>
#include <iostream>
#include "xor_decryptor.hpp"
#include "text_evaluator.hpp"

XorDecryptor::PlaintextResult XorDecryptor::decrypt_hex(const std::string &hex_ciphertext) const {
    auto binary = Botan::hex_decode(hex_ciphertext);
    return decrypt(binary);
}

XorDecryptor::PlaintextResult XorDecryptor::decrypt(const std::vector<uint8_t> &ciphertext) const {
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

    return PlaintextResult(result, max_score);
}

XorDecryptor::PlaintextResult XorDecryptor::decrypt_best_hex(const std::vector<std::string> &ciphertexts) const {
    std::vector<std::vector<uint8_t>> binary_ciphertexts;
    for (const auto &ciphertext : ciphertexts) {
        binary_ciphertexts.emplace_back(Botan::hex_decode(ciphertext));
    }
    return decrypt_best(binary_ciphertexts);
}

XorDecryptor::PlaintextResult XorDecryptor::decrypt_best(const std::vector<std::vector<uint8_t >> &ciphertexts) const {
    PlaintextResult best_candidate("", -1);
    for (const auto &ciphertext : ciphertexts) {
        auto candidate = decrypt(ciphertext);
        if (candidate.score > best_candidate.score) {
            best_candidate = candidate;
        }
    }

    return best_candidate;
}

XorDecryptor::PlaintextResult::PlaintextResult(const std::string &text, int score) : text(text), score(score) {
}
