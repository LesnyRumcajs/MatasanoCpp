#include "gtest/gtest.h"
#include "../../text_evaluator.hpp"
#include "../../xor_decryptor.hpp"
/**
 * Single-byte XOR cipher
*/

namespace {

    TEST(TextEvaluatorTest, PrintableOverBinarySingleCharacter) {
        const char printable_char{'a'};
        const char binary_char{'\x01'};

        TextEvaluator evaluator;
        auto printable_score = evaluator.score(printable_char);
        auto binary_score = evaluator.score(binary_char);
        EXPECT_GT(printable_score, binary_score);
    }

    TEST(TextEvaluatorTest, PrintableOverBinaryString) {
        const std::string printable_string{"test"};
        const std::string binary_string{"\x01est"};

        TextEvaluator evaluator;
        auto printable_score = evaluator.score(printable_string);
        auto binary_score = evaluator.score(binary_string);
        EXPECT_GT(printable_score, binary_score);
    }

    TEST(TextEvaluatorTest, PrintableOveryBinaryVector) {
        const std::vector<uint8_t> printables{'a', 'b', 'c', 'd'};
        const std::vector<uint8_t> binaries{'\x00', '\x01', '\x02', '\x03'};

        TextEvaluator evaluator;
        auto printable_score = evaluator.score(printables);
        auto binary_score = evaluator.score(binaries);
        EXPECT_GT(printable_score, binary_score);
    }

    TEST(TextEvaluatorTest, EmptyContainers) {
        const std::string empty_string;
        const std::vector<uint8_t> empty_vector;

        TextEvaluator evaluator;
        auto empty_string_score = evaluator.score(empty_string);
        auto empty_vector_score = evaluator.score(empty_vector);

        EXPECT_EQ(empty_string_score, empty_vector_score);
    }

    TEST(XorDecryptorTest, DecryptChallenge) {
        const std::string input{"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};
        const std::string expected{"Cooking MC's like a pound of bacon"};

        XorDecryptor decryptor;
        auto result = decryptor.decrypt_hex(input).text;
        EXPECT_EQ(expected, result);
    }
}
