/**
 * Break repeating-key XOR
*/

#include <gtest/gtest.h>
#include "../../crypto_functions.hpp"
#include "../../xor/xor_breaker.hpp"

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

    TEST(XorBreakerTest, ShouldLoadFromBase64WithNoException) {
        std::string sample_base64("dGVzdA=="); // "test"

        XorBreaker breaker;
        EXPECT_NO_THROW(breaker.load_from_base64(sample_base64));
    }

    TEST(XorBreakerTest, GivenNoCiphertextShouldThrow) {
        XorBreaker breaker;
        EXPECT_THROW(breaker.decrypt(), std::runtime_error);
    }

    TEST(XorBreakerTest, GivenChallengeShouldCorrectlyDecrypt) {
        std::ifstream file("../res/set1/6.txt");

        std::string base64_ciphertext{std::istream_iterator<char>{file},
                                      std::istream_iterator<char>{}};

        XorBreaker breaker;
        EXPECT_NO_THROW(breaker.load_from_base64(base64_ciphertext));

        std::string expected(
                "I'm back and I'm ringin' the bell \nA rockin' on the mike while the fly "
                "girls yell \nIn ecstasy in the back of me \nWell that's my DJ Deshay "
                "cuttin' all them Z's \nHittin' hard and the girlies goin' crazy "
                "\nVanilla's on the mike, man I'm not lazy. \n\nI'm lettin' my drug kick "
                "in \nIt controls my mouth and I begin \nTo just let it flow, let my "
                "concepts go \nMy posse's to the side yellin', Go Vanilla Go! \n\nSmooth "
                "'cause that's the way I will be \nAnd if you don't give a damn, then "
                "\nWhy you starin' at me \nSo get off 'cause I control the stage "
                "\nThere's no dissin' allowed \nI'm in my own phase \nThe girlies sa y "
                "they love me and that is ok \nAnd I can dance better than any kid n' "
                "play \n\nStage 2 -- Yea the one ya' wanna listen to \nIt's off my head "
                "so let the beat play through \nSo I can funk it up and make it sound "
                "good \n1-2-3 Yo -- Knock on some wood \nFor good luck, I like my rhymes "
                "atrocious \nSupercalafragilisticexpialidocious \nI'm an effect and that "
                "you can bet \nI can take a fly girl and make her wet. \n\nI'm like "
                "Samson -- Samson to Delilah \nThere's no denyin', You can try to hang "
                "\nBut you'll keep tryin' to get my style \nOver and over, practice "
                "makes perfect \nBut not if you're a loafer. \n\nYou'll get nowhere, no "
                "place, no time, no girls \nSoon -- Oh my God, homebody, you probably "
                "eat \nSpaghetti with a spoon! Come on and say it! \n\nVIP. Vanilla Ice "
                "yep, yep, I'm comin' hard like a rhino \nIntoxicating so you stagger "
                "like a wino \nSo punks stop trying and girl stop cryin' \nVanilla Ice "
                "is sellin' and you people are buyin' \n'Cause why the freaks are "
                "jockin' like Crazy Glue \nMovin' and groovin' trying to sing along "
                "\nAll through the ghetto groovin' this here song \nNow you're amazed by "
                "the VIP posse. \n\nSteppin' so hard like a German Nazi \nStartled by "
                "the bases hittin' ground \nThere's no trippin' on mine, I'm just "
                "gettin' down \nSparkamatic, I'm hangin' tight like a fanatic \nYou "
                "trapped me once and I thought that \nYou might have it \nSo step down "
                "and lend me your ear \n'89 in my time! You, '90 is my year. \n\nYou're "
                "weakenin' fast, YO! and I can tell it \nYour body's gettin' hot, so, so "
                "I can smell it \nSo don't be mad and don't be sad \n'Cause the lyrics "
                "belong to ICE, You can call me Dad \nYou're pitchin' a fit, so step "
                "back and endure \nLet the witch doctor, Ice, do the dance to cure \nSo "
                "come up close and don't be square \nYou wanna battle me -- Anytime, "
                "anywhere \n\nYou thought that I was weak, Boy, you're dead wrong \nSo "
                "come on, everybody and sing this song \n\nSay -- Play that funky music "
                "Say, go white boy, go white boy go \nplay that funky music Go white "
                "boy, go white boy, go \nLay down and boogie and play that funky music "
                "till you die. \n\nPlay that funky music Come on, Come on, let me hear "
                "\nPlay that funky music white boy you say it, say it \nPlay that funky "
                "music A little louder now \nPlay that funky music, white boy Come on, "
                "Come on, Come on \nPlay that funky music \n");


        auto result = breaker.decrypt();
        EXPECT_EQ(result.result, expected);
        EXPECT_GT(result.score, 0);
    }

}
