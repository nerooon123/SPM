#include "core/auth.h"
#include "core/crypto.h"
#include <fstream>
#include <stdexcept>
#include <openssl/sha.h>

static const std::string AUTH_FILE = "auth.dat";
static const size_t SALT_SIZE = 16;

bool UserAuth::isRegistered() {
    std::ifstream f(AUTH_FILE, std::ios::binary);
    return f.good();
}

std::vector<unsigned char> UserAuth::registerMasterPassword(const std::string& masterPassword) {
    if (isRegistered()) {
        throw std::runtime_error("Already registered. Delete auth.dat to re-register.");
    }

    auto salt = Crypto::generateRandomBytes(SALT_SIZE);
    auto key = Crypto::deriveKey(masterPassword, salt);
    // Храним хеш ключа для верификации (не сам ключ)
    std::vector<unsigned char> hash(32);
    SHA256(key.data(), key.size(), hash.data());

    std::ofstream out(AUTH_FILE, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot write auth file");
    out.write(reinterpret_cast<const char*>(salt.data()), salt.size());
    out.write(reinterpret_cast<const char*>(hash.data()), hash.size());
    out.close();

    return key; // возвращаем ключ для немедленного использования
}

std::vector<unsigned char> UserAuth::authenticateAndGetKey(const std::string& masterPassword) {
    if (!isRegistered()) return {};

    std::ifstream in(AUTH_FILE, std::ios::binary);
    if (!in) return {};

    std::vector<unsigned char> salt(SALT_SIZE);
    in.read(reinterpret_cast<char*>(salt.data()), salt.size());
    std::vector<unsigned char> storedHash(32);
    in.read(reinterpret_cast<char*>(storedHash.data()), storedHash.size());
    in.close();

    auto key = Crypto::deriveKey(masterPassword, salt);
    std::vector<unsigned char> hash(32);
    SHA256(key.data(), key.size(), hash.data());

    if (hash == storedHash)
        return key;
    else
        return {};
}