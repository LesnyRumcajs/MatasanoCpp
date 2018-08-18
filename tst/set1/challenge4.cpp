#include <fstream>
#include "gtest/gtest.h"
#include "../../src/xor/xor_decryptor.hpp"

/**
 * Detect single-character XOR
*/

namespace {
    TEST(XorDecryptorTest, XorDecryptorTest_BestFromMultipleStrings_Test) {
        std::ifstream is("../res/set1/4.txt");

        std::vector<std::string> lines{std::istream_iterator<std::string>{is},
                                       std::istream_iterator<std::string>{}};

        XorDecryptor decryptor;
        auto result = decryptor.decrypt_best_hex(lines).text;
        EXPECT_EQ(result, "Now that the party is jumping\n");
    }
}