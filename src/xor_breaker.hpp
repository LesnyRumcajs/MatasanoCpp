#ifndef MATASANOCPP_XOR_BREAKER_HPP
#define MATASANOCPP_XOR_BREAKER_HPP


#include <string>
#include <vector>
#include <botan/secmem.h>

class XorBreaker {
public:
    struct PlaintextCandidate {
        std::string result;
        std::string key;
        int score;

        PlaintextCandidate(std::string result, std::string key, int score);

        PlaintextCandidate();
    };

    /**
     * Loads the ciphertext from base64-encoded string
     * @param ciphertext
     */
    void load_from_base64(const std::string &ciphertext);

    /**
     * Decrypts the ciphertext
     * @return candidate plaintext
     */
    PlaintextCandidate decrypt() const;

private:
    struct KeySizeCandidate {
        size_t key_size;
        double normalized_distance;

        KeySizeCandidate(size_t key_size, double normalized_distance);
    };

    Botan::secure_vector<uint8_t> m_ciphertext;

    std::vector<KeySizeCandidate> generate_keysize_candidates(size_t candidates_count = 3) const;

    std::vector<std::vector<uint8_t>> get_ciphertext_in_blocks(size_t block_size) const;

    double calculate_normalized_distance(size_t block_size) const;

};


#endif //MATASANOCPP_XOR_BREAKER_HPP
