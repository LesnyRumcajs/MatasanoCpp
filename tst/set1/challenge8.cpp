/**
 * Detect AES in ECB mode
*/

#include <gtest/gtest.h>
#include "../../src/ecb_detector.hpp"

namespace {
    TEST(ECBDetectorTest, GivenRepeatedBlocksShouldDetect) {
        EXPECT_TRUE(ECBDetector::is_ecb_encrypted({'1', '1', '1', '1'}, 2));
        EXPECT_TRUE(ECBDetector::is_ecb_encrypted({'1', '2', '1', '2'}, 2));
        EXPECT_TRUE(ECBDetector::is_ecb_encrypted({'1', '2', '1', '1', '1', '2'}, 2));
    }

    TEST(ECBDetectorTest, GivenUniqueBlocksShouldNotDetect) {
        EXPECT_FALSE(ECBDetector::is_ecb_encrypted({'1', '2', '1', '1'}, 2));
        EXPECT_FALSE(ECBDetector::is_ecb_encrypted({'1', '2', '2', '1'}, 2));
        EXPECT_FALSE(ECBDetector::is_ecb_encrypted({'1', '2', '3', '4', '6', '1'}, 2));
    }

    TEST(ECBDetectorTest, GivenChallengeFileShouldDetect) {
        auto result = ECBDetector::is_ecb_in_hex_file("../res/set1/8.txt");
        EXPECT_TRUE(result);
        EXPECT_EQ(result.value(),
                  "d880619740a8a19b7840a8a31c810a3d08649af70dc06f4fd5d2d69c744cd283e2dd052f6b641dbf9d11b0348542bb5708649af70dc06f4fd5d2d69c744cd2839475c9dfdbc1d46597949d9c7e82bf5a08649af70dc06f4fd5d2d69c744cd28397a93eab8d6aecd566489154789a6b0308649af70dc06f4fd5d2d69c744cd283d403180c98c8f6db1f2a3f9c4040deb0ab51b29933f2c123c58386b06fba186a");
    }
}
