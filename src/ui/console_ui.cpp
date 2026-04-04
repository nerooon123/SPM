#include <iostream>
#include <string>

#include "ui/console_ui.h"
#include "utils/colors.h"

void ConsoleUI::run() {
    int choice = 0;
    do
    {
        clearScreen();
        displayBanner();
        displayMenu();
        std::string input = getUserInput("> ");

        if (input.empty()) {
            std::cout << "ERROR: Input cannot be empty.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }
        
        try {
            choice = std::stoi(input);
        }
        catch (const std::invalid_argument&) {
            std::cout << "ERROR: Please enter a number.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }
        catch (const std::out_of_range&) {
            std::cout << "ERROR: Number is too large.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }
        processChoice(choice);
        std::cout << "Press Enter to continue...";
        std::cin.get();
    } while (choice !=6);
}

void ConsoleUI::displayBanner() const {
    std::cout << " ___   ____   __  __ \n";
    std::cout << "/ __) (  _ \\ (  \\/  )\n";
    std::cout << "\\__ \\  )___/  )    ( \n";
    std::cout << "(___/ (__)   (_/\\/\\_)\n";
    std::cout << "by: @nerooon123\n";
}

void ConsoleUI::displayMenu() const {
    std::cout << Color::BOLD_CYAN << "--- Password Manager ---\n";
    std::cout << Color::BOLD_GREEN << "1. Add password\n";
    std::cout << Color::BOLD_WHITE << "2. Show list of services\n";
    std::cout << Color::BOLD_WHITE << "3. Find password by service\n";
    std::cout << Color::BOLD_WHITE << "4. Remove password\n";
    std::cout << Color::BOLD_WHITE << "5. Change password\n";
    std::cout << Color::BOLD_RED << "6. Exit\n" << Color::RESET;
}

std::string ConsoleUI::getUserInput(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    if (!std::getline(std::cin, input)) {
        // EOF (Ctrl+D / Ctrl+Z) — exit the program
        std::cout << "\nEOF detected. Exiting.\n";
        std::exit(0);
    }
    return input;
}

void ConsoleUI::processChoice(int choice) {
    switch (choice) {
    case 1:
        std::cout << "Password added.\n";
        break;
    case 2:
        std::cout << "Feature in development.\n";
        break;
    case 3:
        std::cout << "Feature in development.\n";
        break;
    case 4:
        std::cout << "Feature in development.\n";
        break;
    case 5:
        std::cout << "Feature in development.\n";
        break;
    case 6:
        std::cout << "Bye! :(\n";
        break;
    default:
        std::cout << "Invalid option.\n";
    }
}

void ConsoleUI::clearScreen() const {
    std::cout << "\033[2J\033[H";
}