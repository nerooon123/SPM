#pragma once
#include <vector>
#include <string>

class UserAuth {
public:
    // Проверяет, существует ли уже файл с мастер-паролем
    static bool isRegistered();

    // Регистрация: создаёт файл auth.dat, возвращает ключ шифрования
    static std::vector<unsigned char> registerMasterPassword(const std::string& masterPassword);

    // Аутентификация: при успехе возвращает ключ, иначе пустой вектор
    static std::vector<unsigned char> authenticateAndGetKey(const std::string& masterPassword);
};