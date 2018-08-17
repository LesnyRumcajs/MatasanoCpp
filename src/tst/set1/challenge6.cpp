/**
 * Break repeating-key XOR
*/

#include <gtest/gtest.h>
#include "../../crypto_functions.hpp"

namespace {
    TEST(HammingDistanceTest, EmptyContainersShouldReturnZero) {
        EXPECT_EQ(crypto::functions::hamming_distance(std::string(), std::string()), 0);
    }

    TEST(HammingDistanceTest, ContainersOfDifferentSizeShouldThrow) {
        EXPECT_THROW(crypto::functions::hamming_distance(std::string("1"), std::string("11")), std::invalid_argument);
    }

    TEST(HammingDistanceTest, ContaintersOfSameElementsShouldReturnZero) {
        const std::string first = "test";

        EXPECT_EQ(crypto::functions::hamming_distance(first, first), 0);
    }

    TEST(HammingDistanceTest, ShouldCorrectlyComputeDistance) {
        const std::string first{"this is a test"};
        const std::string second{"wokka wokka!!!"};

        EXPECT_EQ(crypto::functions::hamming_distance(first, second), 37);
    }
}
