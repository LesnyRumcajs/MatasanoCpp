#ifndef MATASANOCPP_XOR_DECRYPTOR_HPP
#define MATASANOCPP_XOR_DECRYPTOR_HPP


#include <string>
#include <vector>

class XorDecryptor {
public:
    struct PlaintextResult {
        std::string text;
        int score;

        PlaintextResult(const std::string &text, int score);
    };

    /**
     * Decrypts hex-encoded ciphertext encrypted with single byte key
     * @param hex-encoded ciphertext
     * @return Plaintext with score
     */
    PlaintextResult decrypt_hex(const std::string &hex_ciphertext) const;

    /**
     * Decrypts ciphertext encrypted with single byte key
     * @param encoded ciphertext
     * @return Plaintext with score
     */
    PlaintextResult decrypt(const std::vector<uint8_t> &ciphertext) const;

    /**
     * Decrypts multiple hex-encoded strings and returns plaintext with the highest score
     * @param hex-encoded candidates
     * @return Plaintext with score
     */
    PlaintextResult decrypt_best_hex(const std::vector<std::string> &ciphertexts) const;

    /**
     * Decrypts multiple ciphertext candidates and returns plaintext with the highest score
     * @param hex-encoded candidates
     * @return Plaintext with score
     */
    PlaintextResult decrypt_best(const std::vector<std::vector<uint8_t>> &ciphertexts) const;
};


#endif //MATASANOCPP_XOR_DECRYPTOR_HPP
