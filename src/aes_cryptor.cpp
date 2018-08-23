#include "aes_cryptor.hpp"
#include "padding.hpp"
#include "xor/xor.hpp"

#include <vector>
#include <botan/block_cipher.h>
#include <botan/mode_pad.h>

AESCryptor::AESCryptor(const std::vector<uint8_t> &m_key, const std::vector<uint8_t> &m_iv, bool padding) :
        m_key(m_key),
        m_iv(m_iv),
        m_padding(padding) {
    verify_block_length(m_key);
    verify_block_length(m_iv);

}

std::vector<uint8_t> AESCryptor::encrypt(std::vector<uint8_t> plaintext) const {
    std::vector<uint8_t> ciphertext;

    add_padding(plaintext);
    cbc_encrypt(plaintext, ciphertext);

    return ciphertext;
}

void AESCryptor::cbc_encrypt(std::vector<uint8_t> &plaintext, std::vector<uint8_t> &ciphertext) const {
    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-128"));
    cipher->set_key(m_key);

    auto last_block = m_iv;
    for (auto block = plaintext.begin(); block != plaintext.end(); block += BLOCK_SIZE) {
        last_block = matasano::xor_container({block, block + BLOCK_SIZE}, last_block);
        cipher->encrypt(last_block);
        ciphertext.insert(ciphertext.end(), last_block.begin(), last_block.end());
    }
}

std::vector<uint8_t> AESCryptor::decrypt(std::vector<uint8_t> ciphertext) const {
    if (ciphertext.size() % BLOCK_SIZE) {
        throw std::invalid_argument("invalid ciphertext");
    }

    std::vector<uint8_t> plaintext;
    cbc_decrypt(ciphertext, plaintext);

    remove_padding(plaintext);

    return plaintext;
}

void AESCryptor::cbc_decrypt(std::vector<uint8_t> &ciphertext, std::vector<uint8_t> &plaintext) const {
    std::unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-128"));

    cipher->set_key(m_key);

    auto last_block = m_iv;
    for (auto block = ciphertext.begin(); block != ciphertext.end(); block += BLOCK_SIZE) {
        std::vector<uint8_t> ciphertext_block{block, block + BLOCK_SIZE};
        cipher->decrypt(&*block);
        auto plaintext_chunk = matasano::xor_container({block, block + BLOCK_SIZE}, last_block);

        last_block = ciphertext_block;
        plaintext.insert(plaintext.end(), plaintext_chunk.begin(), plaintext_chunk.end());
    }
}

void AESCryptor::remove_padding(std::vector<uint8_t> &plaintext) const {
    if (m_padding) {
        Botan::PKCS7_Padding padding;
        auto unpad = padding.unpad(plaintext.data(), plaintext.size());
        plaintext.resize(unpad);
    }
}

void AESCryptor::verify_block_length(const std::vector<uint8_t> &block) const {
    if (block.size() != BLOCK_SIZE)
        throw std::invalid_argument("wrong argument length!");
}

void AESCryptor::add_padding(std::vector<uint8_t> &plaintext) const {
    if (m_padding) {
        crypto::padding::add_PKCS7_padding(plaintext);
    } else if (plaintext.size() % BLOCK_SIZE != 0) {
        throw std::invalid_argument("Invalid plaintext size (padding off)");
    }
}
