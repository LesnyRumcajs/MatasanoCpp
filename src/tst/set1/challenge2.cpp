#include "gtest/gtest.h"

/**
 Write a function that takes two equal-length buffers and produces their XOR combination.

If your function works properly, then when you feed it the string:

1c0111001f010100061a024b53535009181c

... after hex decoding, and when XOR'd against:

686974207468652062756c6c277320657965

... should produce:

746865206b696420646f6e277420706c6179
 */


namespace {
    TEST(XorTest, FixedXorAllZeroes) {
        EXPECT_EQ(matasano::xor_hex("00", "00"), "00");
    }

    TEST(XorTest, XorContainerAllZeroes) {
        std::vector<uint8_t> given {0,0};
        std::vector<uint8_t> expected {0,0};
        EXPECT_EQ(matasano::xor_container(given, given), expected);
    }

    TEST(XorTest, FixedXorShouldCorrectlyXor) {
        auto result = matasano::xor_hex("1c0111001f010100061a024b53535009181c",
                                        "686974207468652062756c6c277320657965");
        auto expected{"746865206b696420646f6e277420706c6179"};

        EXPECT_EQ(result, expected);
    }

    TEST(XorTest, FixedXorShouldThrowWhenInvalidInput) {
        EXPECT_ANY_THROW(matasano::xor_hex("1", "23"));
    }

    TEST(XorTest, FixedXorShouldThrowWhenBuffersNotEqual) {
        EXPECT_THROW(matasano::xor_hex("12", "2445"), std::invalid_argument);
    }
}
