/*
 * An ECB/CBC detection oracle
 */

#include <gtest/gtest.h>

#include "../../src/aes_key_generator.hpp"
#include "../../src/crypto_functions.hpp"
#include "../../src/encryption_oracle.hpp"
#include "../../src/ecb_detector.hpp"

namespace {
    TEST(AESKeyGeneratorTest, GivenIncorrectKeySizeShouldThrow) {
        EXPECT_THROW(AESKeyGenerator().generate(2), std::invalid_argument);
        EXPECT_THROW(AESKeyGenerator().generate(0), std::invalid_argument);
        EXPECT_THROW(AESKeyGenerator().generate(-1), std::invalid_argument);
        EXPECT_THROW(AESKeyGenerator().generate(50), std::invalid_argument);
    }

    TEST(AESKeyGeneratorTest, GivenCorrectKeySizeShouldGenerateRandomKey) {
        size_t key_size = 16;
        AESKeyGenerator generator;
        auto first_key = generator.generate(key_size);
        auto second_key = generator.generate(key_size);

        EXPECT_EQ(first_key.size(), key_size);
        EXPECT_EQ(second_key.size(), key_size);
        EXPECT_NE(first_key, second_key);
    }

    TEST(AES_ECB_EncryptTest, EncryptThenDecryptShouldResultInPlaintext) {
        const std::vector<uint8_t> KEY{'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};
        const std::vector<uint8_t> plaintext{'t', 'e', 's', 't'};

        auto ciphertext = crypto::functions::aes_ecb_encrypt(KEY, plaintext);
        auto decrypt_result = crypto::functions::aes_ecb_decrypt(KEY, ciphertext);
        EXPECT_EQ(plaintext, decrypt_result);
    }

    TEST(EncryptionOracleTest, ShouldCorrectlyDetectModes) {
        std::vector<uint8_t> data(100, 'a');
        auto result = EncryptionOracle().encrypt(data);

        EncryptionOracle::ORACLE_MODE detected_mode = ECBDetector::is_ecb_encrypted(result.first) ?
                                                      EncryptionOracle::ORACLE_MODE::ECB :
                                                      EncryptionOracle::ORACLE_MODE::CBC;

        EXPECT_EQ(result.second, detected_mode);
    }
}
