#include <random>
#include <botan/auto_rng.h>
#include "encryption_oracle.hpp"
#include "aes_key_generator.hpp"
#include "aes_cryptor.hpp"
#include "crypto_functions.hpp"

std::pair<std::vector<uint8_t>, EncryptionOracle::ORACLE_MODE>
EncryptionOracle::encrypt(std::vector<uint8_t> plaintext) {
    auto key = AESKeyGenerator().generate(16);
    auto iv = AESKeyGenerator().generate(16);

    add_random_bytes(plaintext, plaintext.begin());
    add_random_bytes(plaintext, plaintext.end());

    if (static_cast<bool>(generate_random_number(0, 1))) {
        return {crypto::functions::aes_ecb_encrypt(key, plaintext), ORACLE_MODE::ECB};
    } else {
        return {AESCryptor(key, iv).encrypt(plaintext), ORACLE_MODE::CBC};
    }

}

void EncryptionOracle::add_random_bytes(std::vector<uint8_t> &data, std::vector<uint8_t>::iterator iterator) {
    unsigned long bytes_to_add = generate_random_number(5, 10);
    Botan::AutoSeeded_RNG rng;

    std::vector<uint8_t> bytes(bytes_to_add);
    rng.randomize(bytes.data(), bytes_to_add);

    data.insert(iterator, bytes.begin(), bytes.end());
}

unsigned long EncryptionOracle::generate_random_number(unsigned long lower_bound, unsigned long upper_bound) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(lower_bound, upper_bound);

    return dist(rng);
}
