#pragma once

#include <string>

class ConsoleUI {
public:
    void run();

private:
    void displayBanner() const;
    void displayMenu() const;
    std::string getUserInput(const std::string& prompt) const;
    void processChoice(int choice);
    void clearScreen() const;
};