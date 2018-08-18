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
     * @return ciphertext
     */
    std::vector<uint8_t> encrypt(const std::string &plaintext) const;

    /**
     * Decrypts the plaintext with a repeating-key xor
     * @param ciphertext
     * @return plaintext
     */
    std::string decrypt(const std::vector<uint8_t> &ciphertext) const;

private:
    std::vector<uint8_t> crypt(const std::vector<uint8_t> &ciphertext) const;
    const std::vector<uint8_t> m_key;
};


#endif //MATASANOCPP_XOR_ENCRYPTOR_HPP
