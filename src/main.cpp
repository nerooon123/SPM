#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>

int main() {
    // 1. Версия OpenSSL
    std::cout << "OpenSSL version: " << OpenSSL_version(OPENSSL_VERSION) << std::endl;

    // 2. Данные для хеширования
    const char* data = "Hello, OpenSSL 3.0!";

    // 3. Вычисление SHA-256 через EVP
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        std::cerr << "Ошибка создания контекста" << std::endl;
        return 1;
    }

    const EVP_MD* md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;

    EVP_DigestInit_ex(ctx, md, nullptr);
    EVP_DigestUpdate(ctx, data, strlen(data));
    EVP_DigestFinal_ex(ctx, hash, &hash_len);

    EVP_MD_CTX_free(ctx);

    // 4. Вывод хеша в hex
    std::cout << "SHA-256 of \"" << data << "\": ";
    for (unsigned int i = 0; i < hash_len; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::dec << std::endl;

    return 0;
}