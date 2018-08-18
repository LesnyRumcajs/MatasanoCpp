#include <botan/mode_pad.h>
#include <botan/block_cipher.h>
#include <botan/base64.h>
#include "crypto_functions.hpp"

std::vector<uint8_t>
crypto::functions::aes_ecb_decrypt(const std::vector<uint8_t> &key, const std::vector<uint8_t> &ciphertext) {
    std::vector<uint8_t> plaintext(ciphertext.size());

    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-128"));
    cipher->set_key(key);
    cipher->decrypt(ciphertext, plaintext);

    Botan::PKCS7_Padding padding;
    auto unpad = padding.unpad(plaintext.data(), plaintext.size());
    plaintext.resize(unpad);

    return plaintext;
}
