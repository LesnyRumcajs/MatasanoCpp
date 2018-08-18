#include <map>
#include <unordered_set>
#include <fstream>
#include <botan/hex.h>
#include "ecb_detector.hpp"
#include "tools_stl.hpp"


bool ECBDetector::is_ecb_encrypted(const std::vector<uint8_t> &ciphertext, size_t block_size) {
    std::unordered_set<std::vector<uint8_t>, tools::stl::VectorHash<uint8_t>> blocks;
    for (auto it = ciphertext.begin(); it < ciphertext.end(); it += block_size) {
        auto result = blocks.insert({it, it + block_size});
        if (!result.second) {
            return true;
        }
    }
    return false;
}

std::experimental::optional<std::string> ECBDetector::is_ecb_in_hex_file(const std::string &path, size_t block_size) {
    std::ifstream is(path);

    std::string str;
    while (std::getline(is, str)) {
        if (is_ecb_encrypted({str.begin(), str.end()}, block_size * 2)) {
            return str;
        }
    }

    return {};
}
