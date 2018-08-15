#ifndef MATASANOCPP_XOR_DECRYPTOR_HPP
#define MATASANOCPP_XOR_DECRYPTOR_HPP


#include <string>
#include <vector>

class XorDecryptor {
public:
    std::string decrypt_hex(const std::string &hex_ciphertext) const;

    std::string decrypt(const std::vector<uint8_t> &ciphertext) const;
};


#endif //MATASANOCPP_XOR_DECRYPTOR_HPP
