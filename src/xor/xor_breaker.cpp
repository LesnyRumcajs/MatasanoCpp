#include <botan/base64.h>
#include <iostream>
#include <utility>
#include <botan/hex.h>
#include "xor_breaker.hpp"
#include "../crypto_functions.hpp"
#include "xor_decryptor.hpp"
#include "xor_encryptor.hpp"
#include "../text_evaluator.hpp"

void XorBreaker::load_from_base64(const std::string &ciphertext) {
    m_ciphertext = Botan::base64_decode(ciphertext);
}

XorBreaker::PlaintextCandidate XorBreaker::decrypt() const {
    if (m_ciphertext.empty()) {
        throw std::runtime_error("No ciphertext to decrypt!");
    }

    XorDecryptor decryptor;
    PlaintextCandidate result;

    auto keysize_candidates = generate_keysize_candidates(6);
    for (const auto &keysize_candidate : keysize_candidates) {
        auto transposed = get_ciphertext_in_blocks(keysize_candidate.key_size);

        std::string key;
        for (const auto &block : transposed) {
            auto partial_result = decryptor.decrypt(block);
            key += static_cast<char>(partial_result.key);
        }

        XorEncryptor encryptor(key);
        auto candidate = encryptor.decrypt({m_ciphertext.begin(), m_ciphertext.end()});
        auto score = TextEvaluator().score(candidate);

        if (score > result.score) {
            result = PlaintextCandidate(std::move(candidate), std::move(key), score);
        }
    }

    return result;
}

std::vector<std::vector<uint8_t>> XorBreaker::get_ciphertext_in_blocks(size_t block_size) const {
    std::vector<std::vector<uint8_t>> result;
    result.resize(block_size);

    for (auto i{0}; i < m_ciphertext.size(); ++i) {
        result.at(i % block_size).push_back(m_ciphertext.at(i));
    }

    return result;
}

std::vector<XorBreaker::KeySizeCandidate> XorBreaker::generate_keysize_candidates(size_t candidates_count) const {
    size_t MIN_KEY_SIZE{2};
    size_t MAX_KEY_SIZE{40};

    if (candidates_count > MAX_KEY_SIZE - MIN_KEY_SIZE) {
        throw std::invalid_argument("Expecting too many candidates!");
    }

    std::vector<KeySizeCandidate> key_size_candidates;
    for (size_t key_size{MIN_KEY_SIZE}; key_size <= MAX_KEY_SIZE; ++key_size) {
        KeySizeCandidate candidate(key_size, calculate_normalized_distance(key_size));
        key_size_candidates.emplace_back(candidate);
    }

    std::nth_element(key_size_candidates.begin(), key_size_candidates.begin() + candidates_count,
                     key_size_candidates.end(), [](const auto &a, const auto &b) {
        return a.normalized_distance < b.normalized_distance;
    });

    return {key_size_candidates.begin(), key_size_candidates.begin() + candidates_count};
}

double XorBreaker::calculate_normalized_distance(size_t block_size) const {
    if (m_ciphertext.size() < 4 * block_size) {
        throw std::invalid_argument("Ciphertext too small for given block size");
    }

    std::array<std::vector<uint8_t>, 4> blocks;
    blocks[0] = {m_ciphertext.begin(), m_ciphertext.begin() + block_size};
    blocks[1] = {m_ciphertext.begin() + block_size, m_ciphertext.begin() + 2 * block_size};
    blocks[2] = {m_ciphertext.begin() + 2 * block_size, m_ciphertext.begin() + 3 * block_size};
    blocks[3] = {m_ciphertext.begin() + 3 * block_size, m_ciphertext.begin() + 4 * block_size};

    return 0.5 * (crypto::functions::hamming_distance(blocks[0], blocks[1]) / 1.0 / block_size +
                  crypto::functions::hamming_distance(blocks[2], blocks[3]) / 1.0 / block_size);
}

XorBreaker::KeySizeCandidate::KeySizeCandidate(size_t key_size, double normalized_distance) : key_size(key_size),
                                                                                              normalized_distance(
                                                                                                      normalized_distance) {

}

XorBreaker::PlaintextCandidate::PlaintextCandidate(std::string result, std::string key, int score)
        : result(std::move(result)), key(std::move(key)), score(score) {

}

XorBreaker::PlaintextCandidate::PlaintextCandidate() : score(0) {}
