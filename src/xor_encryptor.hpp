#ifndef MATASANOCPP_XOR_ENCRYPTOR_HPP
#define MATASANOCPP_XOR_ENCRYPTOR_HPP


#include <string>
#include <vector>

class XorEncryptor {
public:
    explicit XorEncryptor(const std::string &key);

    /**
     * Encrypt the plaintext with a repeating-key xor
     * @param plaintext
     * @return hex-encoded ciphertext
     */
    std::string encrypt_hex(const std::string &plaintext) const;

private:
    const std::vector<uint8_t> m_key;
};


#endif //MATASANOCPP_XOR_ENCRYPTOR_HPP
