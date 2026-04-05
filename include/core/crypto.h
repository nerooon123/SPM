#pragma once
#include <vector>
#include <string>

struct EncryptedData {
    std::vector<unsigned char> iv;        // 12 байт
    std::vector<unsigned char> ciphertext;
    std::vector<unsigned char> tag;       // 16 байт
};

class Crypto {
public:
    // Генерация случайных байт
    static std::vector<unsigned char> generateRandomBytes(size_t length);

    // Вывод ключа из пароля и соли (PBKDF2-HMAC-SHA256)
    static std::vector<unsigned char> deriveKey(const std::string& password,
        const std::vector<unsigned char>& salt);

    // Шифрование (AES-256-GCM)
    static EncryptedData encrypt(const std::vector<unsigned char>& plaintext,
        const std::vector<unsigned char>& key);

    // Дешифрование
    static std::vector<unsigned char> decrypt(const EncryptedData& data,
        const std::vector<unsigned char>& key);
};