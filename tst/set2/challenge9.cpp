/**
Implement PKCS#7 padding
*/

#include <gtest/gtest.h>
#include "../../src/padding.hpp"

namespace {
    TEST(PaddingTest, GivenEmptyDataShouldFillWithBlockSize) {
        std::vector<uint8_t> result;

        size_t block_size{2};
        std::vector<uint8_t> expected{2, 2};

        crypto::padding::add_PKCS7_padding(result, block_size);

        EXPECT_EQ(result, expected);
    }

    TEST(PaddingTest, GivenBlockSizedDataShouldAddBlockSizeWorthOfBytes) {
        std::vector<uint8_t> result{2, 2};

        size_t block_size{2};
        std::vector<uint8_t> expected{2, 2, 2, 2};

        crypto::padding::add_PKCS7_padding(result, block_size);

        EXPECT_EQ(result, expected);
    }

    TEST(PaddingTest, GivenNonBlockSizeDataShouldCorrectlyAddPadding) {
        std::vector<uint8_t> result{'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};

        size_t block_size{20};
        std::string expected{"YELLOW SUBMARINE\x04\x04\x04\x04"};

        crypto::padding::add_PKCS7_padding(result, block_size);

        EXPECT_EQ(result, std::vector<uint8_t>(expected.begin(), expected.end()));
    }
}