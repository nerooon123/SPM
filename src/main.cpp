#include <iostream>

#include "ui/console_ui.h"


int main() {
	try {
		ConsoleUI ui;
		ui.run();
	}
	catch (const std::exception& e) {
		std::cerr << "A critical ERROR has occurred: " << e.what() << std::endl;
		return 1;
	}
}