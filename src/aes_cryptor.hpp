#ifndef MATASANOCPP_AES_CRYPTOR_HPP
#define MATASANOCPP_AES_CRYPTOR_HPP


#include <cstdint>
#include <vector>

class AESCryptor {
public:
    explicit AESCryptor(const std::vector<uint8_t> &m_key,
                        const std::vector<uint8_t> &m_iv = std::vector<uint8_t>(BLOCK_SIZE, 0), bool padding = true);

    std::vector<uint8_t> encrypt(std::vector<uint8_t> plaintext) const;

    std::vector<uint8_t> decrypt(std::vector<uint8_t> ciphertext) const;

private:
    static constexpr int BLOCK_SIZE = 16;
    const std::vector<uint8_t> m_key;
    const std::vector<uint8_t> m_iv;
    const bool m_padding;

    void verify_block_length(const std::vector<uint8_t> &block) const;

    void add_padding(std::vector<uint8_t> &plaintext) const;

    void remove_padding(std::vector<uint8_t> &plaintext) const;

    void cbc_encrypt(std::vector<uint8_t> &plaintext, std::vector<uint8_t> &ciphertext) const;

    void cbc_decrypt(std::vector<uint8_t> &ciphertext, std::vector<uint8_t> &plaintext) const;
};

#endif //MATASANOCPP_AES_CRYPTOR_HPP
