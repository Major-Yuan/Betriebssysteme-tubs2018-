#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plist.h"
#include "shellutils.h"
#include "shellfunctions.h"
#include "colorCodes.h"

int main() {
    char * cmds[] = {"ls", "ls -l", "ps", " "};
	setbuf(stdout, NULL);
	PRINTP("6P if execution correct, 1P if exit status is correct");
    for(int i = 0; i < 4; i++){
        char * cmd = malloc(strlen(cmds[i])+1);
        strcpy(cmd, cmds[i]);
        if(i == 3)
        {
			PRINTP("1P if correct response to empty command");
        }
        printf(COLOR_MESSAGE"Executing \""COLOR_COMMAND"%s"COLOR_MESSAGE"\":"COLOR_RESET"\n", cmd);
        execute_command(cmd);
        free(cmd);
    }

	PRINTP("1P if error caught and exit status correct");
    char non_existend_prog [] = "non_existent_prog";
    printf(COLOR_MESSAGE"Executing \""COLOR_COMMAND"%s"COLOR_MESSAGE"\",  Exitstatus should be 1:"COLOR_RESET"\n", non_existend_prog);
    execute_command(non_existend_prog);

    char non_existend_opt [] = "sleep -x";
    printf("\n"COLOR_MESSAGE"Executing \""COLOR_COMMAND"%s"COLOR_MESSAGE"\", Exitstatus should be 1:"COLOR_RESET"\n", non_existend_opt);
    execute_command(non_existend_opt);
}
