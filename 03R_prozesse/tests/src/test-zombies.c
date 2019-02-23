#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plist.h"
#include "shellutils.h"
#include "shellfunctions.h"
#include "colorCodes.h"

int main() {
    char ps [] = "ps";
    char sleep_background [] = "sleep 1 &";
	setbuf(stdout, NULL);
    printf("\n"COLOR_MESSAGE"Creating zombie:"COLOR_RESET"\n");
	fflush(stdout);
    execute_command(sleep_background);
    sleep(1);
    printf("\n"COLOR_MESSAGE"There should be \""COLOR_COMMAND"sleep <defunct>"COLOR_MESSAGE"\" in the following \""COLOR_COMMAND"ps"COLOR_MESSAGE"\":"COLOR_RESET"\n");
	fflush(stdout);
    execute_command(ps);
	fflush(stdout);
    printf("\n\t"COLOR_POINTS"2P if sleep <defunct> collected"COLOR_RESET"\n");
    printf("\n"COLOR_MESSAGE"Killing zombie:"COLOR_RESET"\n");
    collect_defunct_process();
    printf("\n"COLOR_MESSAGE"The zombie should be dead:"COLOR_RESET"\n");
    execute_command(ps);
}
