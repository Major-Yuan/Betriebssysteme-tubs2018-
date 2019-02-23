#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plist.h"
#include "shellutils.h"
#include "shellfunctions.h"
#include "colorCodes.h"

int main() {
	setbuf(stdout, NULL);
    char command_line[COMMAND_LINE_MAXIMUM];
	PRINTP("1P if command gotten, 1P if quitting with STRG+D");
    printf(COLOR_MESSAGE"Read input (input required):"COLOR_RESET"\n");
    read_input(command_line, COMMAND_LINE_MAXIMUM, stdin);
    execute_command(command_line);
	printf("\n");
}
