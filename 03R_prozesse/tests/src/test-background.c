#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plist.h"
#include "shellutils.h"
#include "shellfunctions.h"
#include "colorCodes.h"

int main() {
    char ps  [] = "ps";
    char sleep_background [] = "sleep 4 &";
	setbuf(stdout, NULL);
    printf("\n\t"COLOR_POINTS"1P if sleep was launched in the background"COLOR_RESET"\n");
    printf("\n%s\n"COLOR_MESSAGE"\""COLOR_COMMAND"ps"COLOR_MESSAGE"\" should show \""COLOR_COMMAND"sleep"COLOR_MESSAGE"\" as process:"COLOR_RESET"\n", sleep_background);
    sleep(1);
    execute_command(sleep_background);
    execute_command(ps);
    printf("\n\t"COLOR_POINTS"1P if sleep was collected or is defunct"COLOR_RESET"\n");
    printf("\n"COLOR_MESSAGE"Waiting for \""COLOR_COMMAND"%s"COLOR_MESSAGE"\" to finish \n\""COLOR_COMMAND"ps"COLOR_MESSAGE"\" should show \""COLOR_COMMAND"sleep"COLOR_MESSAGE"\" either as <defunct> or not at all:"COLOR_RESET"\n", sleep_background);
    sleep(5);
    execute_command(ps);
}
