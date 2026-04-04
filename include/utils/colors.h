#pragma once

#include <string>

namespace Color {
	// Basic colors
	inline const std::string RESET = "\033[0m";
	inline const std::string BLACK = "\033[30m";
	inline const std::string RED = "\033[31m";
	inline const std::string GREEN = "\033[32m";
	inline const std::string YELLOW = "\033[33m";
	inline const std::string BLUE = "\033[34m";
	inline const std::string MAGENTA = "\033[35m";
	inline const std::string CYAN = "\033[36m";
	inline const std::string WHITE = "\033[37m";

	// Bright (bold) colors
	inline const std::string BOLD_BLACK = "\033[1;30m";
	inline const std::string BOLD_RED = "\033[1;31m";
	inline const std::string BOLD_GREEN = "\033[1;32m";
	inline const std::string BOLD_YELLOW = "\033[1;33m";
	inline const std::string BOLD_BLUE = "\033[1;34m";
	inline const std::string BOLD_MAGENTA = "\033[1;35m";
	inline const std::string BOLD_CYAN = "\033[1;36m";
	inline const std::string BOLD_WHITE = "\033[1;37m";

	// Background colors (optional)
	inline const std::string BG_BLACK = "\033[40m";
	inline const std::string BG_RED = "\033[41m";
	inline const std::string BG_GREEN = "\033[42m";
	inline const std::string BG_YELLOW = "\033[43m";
	inline const std::string BG_BLUE = "\033[44m";
	inline const std::string BG_MAGENTA = "\033[45m";
	inline const std::string BG_CYAN = "\033[46m";
	inline const std::string BG_WHITE = "\033[47m";

}