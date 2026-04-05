#include "core/crypto.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdexcept>
#include <cstring>

std::vector<unsigned char> Crypto::generateRandomBytes(size_t length) {
    std::vector<unsigned char> buffer(length);
    if (RAND_bytes(buffer.data(), static_cast<int>(length)) != 1) {
        throw std::runtime_error("RAND_bytes failed");
    }
    return buffer;
}

std::vector<unsigned char> Crypto::deriveKey(const std::string& password,
    const std::vector<unsigned char>& salt) {
    std::vector<unsigned char> key(32); // 256 bit
    if (PKCS5_PBKDF2_HMAC(password.c_str(), password.size(),
        salt.data(), salt.size(),
        100000, EVP_sha256(),
        key.size(), key.data()) != 1) {
        throw std::runtime_error("PBKDF2 key derivation failed");
    }
    return key;
}

EncryptedData Crypto::encrypt(const std::vector<unsigned char>& plaintext,
    const std::vector<unsigned char>& key) {
    EncryptedData result;
    result.iv = generateRandomBytes(12); // GCM recommended nonce length
    result.ciphertext.resize(plaintext.size());
    result.tag.resize(16);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("EVP_CIPHER_CTX_new failed");

    int outlen = 0;
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1 ||
        EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(), result.iv.data()) != 1 ||
        EVP_EncryptUpdate(ctx, result.ciphertext.data(), &outlen, plaintext.data(), static_cast<int>(plaintext.size())) != 1 ||
        EVP_EncryptFinal_ex(ctx, result.ciphertext.data() + outlen, &outlen) != 1 ||
        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, result.tag.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encryption failed");
    }
    EVP_CIPHER_CTX_free(ctx);
    return result;
}

std::vector<unsigned char> Crypto::decrypt(const EncryptedData& data,
    const std::vector<unsigned char>& key) {
    std::vector<unsigned char> plaintext(data.ciphertext.size());
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("EVP_CIPHER_CTX_new failed");

    int outlen = 0;
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1 ||
        EVP_DecryptInit_ex(ctx, nullptr, nullptr, key.data(), data.iv.data()) != 1 ||
        EVP_DecryptUpdate(ctx, plaintext.data(), &outlen, data.ciphertext.data(), static_cast<int>(data.ciphertext.size())) != 1 ||
        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, const_cast<unsigned char*>(data.tag.data())) != 1 ||
        EVP_DecryptFinal_ex(ctx, plaintext.data() + outlen, &outlen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Decryption failed (wrong password or corrupted data)");
    }
    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}