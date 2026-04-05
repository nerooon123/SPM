#include "core/storage.h"
#include "core/crypto.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

static const std::string VAULT_FILE = "vault.dat";

std::vector<Entry> Storage::load(const std::vector<unsigned char>& key) {
    std::ifstream in(VAULT_FILE, std::ios::binary);
    if (!in) return {}; // файла нет – пустое хранилище

    // Читаем весь файл
    std::vector<unsigned char> encryptedData((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    in.close();
    if (encryptedData.empty()) return {};

    // Формат: iv (12) + tag (16) + ciphertext
    if (encryptedData.size() < 12 + 16) {
        throw std::runtime_error("Corrupted vault file");
    }

    EncryptedData data;
    data.iv.assign(encryptedData.begin(), encryptedData.begin() + 12);
    data.tag.assign(encryptedData.begin() + 12, encryptedData.begin() + 12 + 16);
    data.ciphertext.assign(encryptedData.begin() + 12 + 16, encryptedData.end());

    std::vector<unsigned char> plain = Crypto::decrypt(data, key);
    std::string plainText(plain.begin(), plain.end());

    std::vector<Entry> entries;
    std::istringstream iss(plainText);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty()) continue;
        std::istringstream lineStream(line);
        std::string service, username, password;
        if (std::getline(lineStream, service, '|') &&
            std::getline(lineStream, username, '|') &&
            std::getline(lineStream, password)) {
            entries.push_back({ service, username, password });
        }
    }
    return entries;
}

void Storage::save(const std::vector<Entry>& entries, const std::vector<unsigned char>& key) {
    std::ostringstream oss;
    for (const auto& e : entries) {
        oss << e.service << '|' << e.username << '|' << e.password << '\n';
    }
    std::string plain = oss.str();
    std::vector<unsigned char> plainVec(plain.begin(), plain.end());

    EncryptedData encrypted = Crypto::encrypt(plainVec, key);

    std::ofstream out(VAULT_FILE, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot write vault file");

    out.write(reinterpret_cast<const char*>(encrypted.iv.data()), encrypted.iv.size());
    out.write(reinterpret_cast<const char*>(encrypted.tag.data()), encrypted.tag.size());
    out.write(reinterpret_cast<const char*>(encrypted.ciphertext.data()), encrypted.ciphertext.size());
    out.close();
}