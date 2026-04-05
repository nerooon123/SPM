#include <ui/console_ui.h>
#include <utils/colors.h>
#include <core/auth.h>
#include <core/storage.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>

void ConsoleUI::run() {
    handleAuthentication();
    if (!authenticated) {
        std::cout << "Authentication failed. Exiting.\n";
        return;
    }

    // Загружаем существующие записи
    try {
        entries = Storage::load(currentKey);
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading vault: " << e.what() << std::endl;
        return;
    }

    int choice = 0;
    do {
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
        if (choice != 6) {
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    } while (choice != 6);
}

void ConsoleUI::displayBanner() const {
    std::cout << Color::BOLD_YELLOW << " ___   ____   __  __ \n";
    std::cout << Color::BOLD_YELLOW << "/ __) (  _ \\ (  \\/  )\n";
    std::cout << Color::BOLD_YELLOW << "\\__ \\  )___/  )    ( \n";
    std::cout << Color::BOLD_YELLOW << "(___/ (__)   (_/\\/\\_)\n";
    std::cout << Color::BOLD_YELLOW << "by: @nerooon123\n" << Color::RESET;
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
        std::cout << "\nEOF detected. Exiting.\n";
        std::exit(0);
    }
    return input;
}

void ConsoleUI::processChoice(int choice) {
    switch (choice) {
    case 1: addPassword(); break;
    case 2: showServices(); break;
    case 3: findPassword(); break;
    case 4: removePassword(); break;
    case 5: changePassword(); break;
    case 6: std::cout << "Bye! :(\n"; break;
    default: std::cout << "Invalid option.\n";
    }
}

void ConsoleUI::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}

void ConsoleUI::handleAuthentication() {
    if (!UserAuth::isRegistered()) {
        std::cout << "=== FIRST TIME SETUP ===\n";
        std::string pwd1 = getUserInput("Create master password: ");
        std::string pwd2 = getUserInput("Confirm master password: ");
        if (pwd1 != pwd2) {
            std::cout << "Passwords do not match. Exiting.\n";
            return;
        }
        try {
            currentKey = UserAuth::registerMasterPassword(pwd1);
            authenticated = true;
            std::cout << "Master password registered successfully.\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Registration error: " << e.what() << std::endl;
        }
    }
    else {
        std::string pwd;
        do {
            pwd = getUserInput("Enter master password: ");
            currentKey = UserAuth::authenticateAndGetKey(pwd);
            if (currentKey.empty()) {
                std::cout << "Wrong password. Try again.\n";
            }
            else {
                authenticated = true;
            }
        } while (!authenticated);
    }
}

void ConsoleUI::addPassword() {
    std::string service = getUserInput("Service name: ");
    std::string username = getUserInput("Username: ");
    std::string password = getUserInput("Password: ");
    entries.push_back({ service, username, password });
    try {
        Storage::save(entries, currentKey);
        std::cout << "Password added successfully.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving: " << e.what() << std::endl;
    }
}

void ConsoleUI::showServices() {
    if (entries.empty()) {
        std::cout << "No services saved.\n";
        return;
    }
    std::cout << "Saved services:\n";
    for (size_t i = 0; i < entries.size(); ++i) {
        std::cout << i + 1 << ". " << entries[i].service << "\n";
    }
}

void ConsoleUI::findPassword() {
    std::string service = getUserInput("Enter service name: ");
    for (const auto& e : entries) {
        if (e.service == service) {
            std::cout << "Service: " << e.service << "\n";
            std::cout << "Username: " << e.username << "\n";
            std::cout << "Password: " << e.password << "\n";
            return;
        }
    }
    std::cout << "Service not found.\n";
}

void ConsoleUI::removePassword() {
    std::string service = getUserInput("Enter service name to remove: ");
    auto it = std::remove_if(entries.begin(), entries.end(),
        [&](const Entry& e) { return e.service == service; });
    if (it != entries.end()) {
        entries.erase(it, entries.end());
        try {
            Storage::save(entries, currentKey);
            std::cout << "Removed successfully.\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error saving: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Service not found.\n";
    }
}

void ConsoleUI::changePassword() {
    std::string service = getUserInput("Enter service name to change: ");
    for (auto& e : entries) {
        if (e.service == service) {
            std::string newPass = getUserInput("New password: ");
            e.password = newPass;
            try {
                Storage::save(entries, currentKey);
                std::cout << "Password updated.\n";
            }
            catch (const std::exception& e) {
                std::cerr << "Error saving: " << e.what() << std::endl;
            }
            return;
        }
    }
    std::cout << "Service not found.\n";
}