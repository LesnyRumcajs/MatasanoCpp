#include "gtest/gtest.h"
#include "../../xor_encryptor.hpp"
#include "../../repeating_key.hpp"

/**
 * Implement repeating-key XOR
*/

namespace {
    TEST(RepeatingKeyTest, GivenEmptyKeyShouldThrow) {
        EXPECT_THROW(RepeatingKey key(""), std::invalid_argument);
    }

    TEST(RepeatingKeyTest, GivenSingleCharacterKeyShoulOutputTheSameChar) {
        const std::string key("1");
        RepeatingKey repeatingKey(key);

        EXPECT_EQ(repeatingKey.next(), key.front());
        EXPECT_EQ(repeatingKey.next(), key.front());
    }

    TEST(RepeatingKeyTest, GivenMultipleCharacterKeyShouldRepeat) {
        const std::string key("123");
        RepeatingKey repeatingKey(key);

        EXPECT_EQ(repeatingKey.next(), key[0]);
        EXPECT_EQ(repeatingKey.next(), key[1]);
        EXPECT_EQ(repeatingKey.next(), key[2]);
        EXPECT_EQ(repeatingKey.next(), key[0]);
        EXPECT_EQ(repeatingKey.next(), key[1]);
        EXPECT_EQ(repeatingKey.next(), key[2]);
    }

    TEST(XorEncryptorTest, EmptyPlaintextShouldReturnEmptyCiphertext) {
        const std::string input;
        const std::string key{"key"};

        XorEncryptor encryptor(key);
        EXPECT_TRUE(encryptor.encrypt_hex(input).empty());
    }

    TEST(XorEncryptorTest, PlaintextWithZeroKeyShouldReturnHexPlaintext) {
        const std::string input{"test"};
        const std::string key(1, 0);

        XorEncryptor encryptor(key);
        EXPECT_EQ(encryptor.encrypt_hex(input), "74657374");
    }

    TEST(XorEncryptorTest, PlaintextWithNoKeyShouldThrow) {

        EXPECT_THROW(XorEncryptor encryptor(""), std::invalid_argument);
    }

    TEST(XorEncryptorTest, PlaintextWithSimpleKey) {
        const std::string input_plaintext{"AAAA"};
        const std::string expected_ciphertext{"40404040"};
        const std::string key{"\x01\x01\x01\x01"};

        XorEncryptor encryptor(key);
        EXPECT_EQ(encryptor.encrypt_hex(input_plaintext), expected_ciphertext);
    }

    TEST(XorEncryptorTest, PlaintextWithChallengeKey) {
        const std::string input_plaintext{
                "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"};
        const std::string expected_ciphertext{
                "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272"
                "a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"};
        const std::string key{"ICE"};

        XorEncryptor encryptor(key);
        EXPECT_EQ(encryptor.encrypt_hex(input_plaintext), expected_ciphertext);
    }
}
