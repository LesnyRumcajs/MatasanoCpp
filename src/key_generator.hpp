#ifndef MATASANOCPP_KEY_GENERATOR_HPP
#define MATASANOCPP_KEY_GENERATOR_HPP


#include <cstdint>
#include <vector>
#include <cstddef>

class KeyGenerator {
public:
    virtual std::vector<uint8_t> generate(size_t key_size) const = 0;

    virtual ~KeyGenerator() = default;

private:
    virtual void validate_key_size(size_t key_size) const = 0;
};


#endif //MATASANOCPP_KEY_GENERATOR_HPP
