#pragma once

#include <string>
#include <vector>
#include <core/storage.h>

class ConsoleUI {
public:
    void run();

private:
    void displayBanner() const;
    void displayMenu() const;
    std::string getUserInput(const std::string& prompt) const;
    void processChoice(int choice);
    void clearScreen() const;

    void handleAuthentication();   // регистрация / вход
    void addPassword();
    void showServices();
    void findPassword();
    void removePassword();
    void changePassword();

    std::vector<Entry> entries;
    std::vector<unsigned char> currentKey;
    bool authenticated = false;
};