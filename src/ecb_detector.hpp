#ifndef MATASANOCPP_ECB_DETECTOR_HPP
#define MATASANOCPP_ECB_DETECTOR_HPP


#include <cstdint>
#include <vector>
#include <experimental/optional>

class ECBDetector {
private:
    static const int DEFAULT_BLOCK_SIZE = 16;
public:
    static bool is_ecb_encrypted(const std::vector<uint8_t> &ciphertext, size_t block_size = DEFAULT_BLOCK_SIZE);

    static std::experimental::optional<std::string> is_ecb_in_hex_file(const std::string &path,
                                                                       size_t block_size = DEFAULT_BLOCK_SIZE);
};


#endif //MATASANOCPP_ECB_DETECTOR_HPP
