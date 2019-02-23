#pragma once

//! USAGE EXAMPLE:
//! printf(COLOR_RED"this will be in red, even the number %d\n"COLOR_RESET, 123);

#define COLOR_RESET "\x1B[0m" /* No Color */

// plain colors
#define COLOR_BLACK  "\x1B[0;30m"
#define COLOR_RED    "\x1B[0;31m"
#define COLOR_GREEN  "\x1B[0;32m"
#define COLOR_ORANGE "\x1B[0;33m"
#define COLOR_BLUE   "\x1B[0;34m"
#define COLOR_PURPLE "\x1B[0;35m"
#define COLOR_CYAN   "\x1B[0;36m"
#define COLOR_GRAY   "\x1B[0;37m"

// BOLD Colors (brighter than plain colors)
#define COLOR_BOLD_GRAY   "\033[1;30m"
#define COLOR_BOLD_RED    "\033[1;31m"
#define COLOR_BOLD_GREEN  "\033[1;32m"
#define COLOR_BOLD_YELLOW "\033[1;33m"
#define COLOR_BOLD_BLUE   "\033[1;34m"
#define COLOR_BOLD_PURPLE "\033[1;35m"
#define COLOR_BOLD_CYAN   "\033[1;36m"
#define COLOR_BOLD_WHITE  "\033[1;37m"

#define COLOR_POINTS  COLOR_ORANGE
#define COLOR_MESSAGE COLOR_CYAN
#define COLOR_COMMAND COLOR_BOLD_WHITE

#define PRINTP(s)\
	printf(COLOR_RESET"\n\t"COLOR_POINTS"%s"COLOR_RESET"\n\n", s)
