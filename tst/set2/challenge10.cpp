/*
 * Implement CBC mode
 */

#include <gtest/gtest.h>
#include <iterator>
#include <fstream>
#include <botan/base64.h>
#include <botan/hex.h>
#include <experimental/string_view>
#include "../../src/aes_cryptor.hpp"

namespace {
    TEST(AESCryptorTest, EncryptDecryptShouldGivePlaintext) {
        std::vector<uint8_t> key{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        AESCryptor cryptor(key);

        std::vector<uint8_t> plaintext{1, 2, 3, 4};
        auto ciphertext = cryptor.encrypt(plaintext);
        auto result = cryptor.decrypt(ciphertext);
        EXPECT_EQ(plaintext, result);
    }

    TEST(AESCryptorTest, GivenIncorrectKeySizeShouldThrow) {
        EXPECT_THROW(AESCryptor({1, 2}), std::invalid_argument);
    }

    TEST(AESCryptorTest, GivenIncorrectIVSizeShouldThrow) {
        EXPECT_THROW(AESCryptor({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, {1, 2}), std::invalid_argument);
    }

    TEST(AESCryptorTest, GivenIncorrectPlaintextSizeWithNoPaddingShouldThrow) {
        std::vector<uint8_t> key{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        std::vector<uint8_t> iv{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        AESCryptor cryptor(key, iv, false);

        std::vector<uint8_t> plaintext{1, 2, 3, 4};
        EXPECT_THROW(cryptor.encrypt(plaintext);, std::invalid_argument);
    }

    TEST(AESCryptorTest, GivenIncorrectCiphertextSizeWithShouldThrow) {
        std::vector<uint8_t> key{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        std::vector<uint8_t> iv{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        AESCryptor cryptor(key, iv);

        std::vector<uint8_t> ciphertext{1, 2, 3, 4};
        EXPECT_THROW(cryptor.decrypt(ciphertext);, std::invalid_argument);
    }

    TEST(AESCryptorTest, GivenTestVectorShouldCorrectlyEncrypt) {
        auto key = Botan::hex_decode("2b7e151628aed2a6abf7158809cf4f3c");
        auto iv = Botan::hex_decode("000102030405060708090A0B0C0D0E0F");
        auto plaintext = Botan::hex_decode("6bc1bee22e409f96e93d7e117393172a");
        auto expected = Botan::hex_decode("7649abac8119b246cee98e9b12e9197d");

        AESCryptor aesCryptor(key, iv, false);
        auto result = aesCryptor.encrypt(plaintext);

        EXPECT_EQ(result, expected);
    }

    TEST(AESCryptorTest, ShouldDecryptChallenge) {
        const std::string expected{
                "I'm back and I'm ringin' the bell \nA rockin' on the mike while the fly girls yell \nIn ecstasy in the back of me \nWell that's my DJ Deshay cuttin' all them Z's \nHittin' hard and the girlies goin' crazy \nVanilla's on the mike, man I'm not lazy. \n\nI'm lettin' my drug kick in \nIt controls my mouth and I begin \nTo just let it flow, let my concepts go \nMy posse's to the side yellin', Go Vanilla Go! \n\nSmooth 'cause that's the way I will be \nAnd if you don't give a damn, then \nWhy you starin' at me \nSo get off 'cause I control the stage \nThere's no dissin' allowed \nI'm in my own phase \nThe girlies sa y they love me and that is ok \nAnd I can dance better than any kid n' play \n\nStage 2 -- Yea the one ya' wanna listen to \nIt's off my head so let the beat play through \nSo I can funk it up and make it sound good \n1-2-3 Yo -- Knock on some wood \nFor good luck, I like my rhymes atrocious \nSupercalafragilisticexpialidocious \nI'm an effect and that you can bet \nI can take a fly girl and make her wet. \n\nI'm like Samson -- Samson to Delilah \nThere's no denyin', You can try to hang \nBut you'll keep tryin' to get my style \nOver and over, practice makes perfect \nBut not if you're a loafer. \n\nYou'll get nowhere, no place, no time, no girls \nSoon -- Oh my God, homebody, you probably eat \nSpaghetti with a spoon! Come on and say it! \n\nVIP. Vanilla Ice yep, yep, I'm comin' hard like a rhino \nIntoxicating so you stagger like a wino \nSo punks stop trying and girl stop cryin' \nVanilla Ice is sellin' and you people are buyin' \n'Cause why the freaks are jockin' like Crazy Glue \nMovin' and groovin' trying to sing along \nAll through the ghetto groovin' this here song \nNow you're amazed by the VIP posse. \n\nSteppin' so hard like a German Nazi \nStartled by the bases hittin' ground \nThere's no trippin' on mine, I'm just gettin' down \nSparkamatic, I'm hangin' tight like a fanatic \nYou trapped me once and I thought that \nYou might have it \nSo step down and lend me your ear \n'89 in my time! You, '90 is my year. \n\nYou're weakenin' fast, YO! and I can tell it \nYour body's gettin' hot, so, so I can smell it \nSo don't be mad and don't be sad \n'Cause the lyrics belong to ICE, You can call me Dad \nYou're pitchin' a fit, so step back and endure \nLet the witch doctor, Ice, do the dance to cure \nSo come up close and don't be square \nYou wanna battle me -- Anytime, anywhere \n\nYou thought that I was weak, Boy, you're dead wrong \nSo come on, everybody and sing this song \n\nSay -- Play that funky music Say, go white boy, go white boy go \nplay that funky music Go white boy, go white boy, go \nLay down and boogie and play that funky music till you die. \n\nPlay that funky music Come on, Come on, let me hear \nPlay that funky music white boy you say it, say it \nPlay that funky music A little louder now \nPlay that funky music, white boy Come on, Come on, Come on \nPlay that funky music \n"};
        std::ifstream is("../res/set2/10.txt");

        std::string base64_ciphertext{std::istream_iterator<char>{is},
                                      std::istream_iterator<char>{}};

        auto ciphertext = Botan::base64_decode(base64_ciphertext);
        const std::vector<uint8_t> key{'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};
        AESCryptor cryptor(key);

        auto result = cryptor.decrypt({ciphertext.begin(), ciphertext.end()});
        EXPECT_EQ(std::experimental::string_view(reinterpret_cast<const char *>(result.data()), result.size()),
                  expected);
    }
}
