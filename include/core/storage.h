#pragma once
#include <vector>
#include <string>

struct Entry {
    std::string service;
    std::string username;
    std::string password;
};

class Storage {
public:
    // Загрузить записи из зашифрованного файла
    static std::vector<Entry> load(const std::vector<unsigned char>& key);

    // Сохранить записи в зашифрованный файл
    static void save(const std::vector<Entry>& entries, const std::vector<unsigned char>& key);
};