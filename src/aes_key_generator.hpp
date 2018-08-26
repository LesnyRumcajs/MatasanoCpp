#ifndef MATASANOCPP_AES_KEY_GENERATOR_HPP
#define MATASANOCPP_AES_KEY_GENERATOR_HPP


#include "key_generator.hpp"

class AESKeyGenerator : public KeyGenerator {
public:
    std::vector<uint8_t> generate(size_t key_size) const override;

private:
    static const int BLOCK_SIZE = 16;

    void validate_key_size(size_t key_size) const override;
};


#endif //MATASANOCPP_AES_KEY_GENERATOR_HPP
