#include "botan-2/botan/base64.h"
#include "botan-2/botan/hex.h"

#include "gtest/gtest.h"

/**
 Convert hex to base64

 The string:

 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d

 Should produce:

 SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

 So go ahead and make that happen. You'll need to use this code for the rest of the exercises.
*/


namespace {
    TEST(Base64Test, ConvertHexToBase64) {
        auto binary_input = Botan::hex_decode("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
        auto base64_output = Botan::base64_encode(binary_input);
        auto expected{"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"};

        EXPECT_EQ(base64_output, expected);
    }
}
