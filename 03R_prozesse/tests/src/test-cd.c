#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "plist.h"
#include "shellutils.h"
#include "shellfunctions.h"
#include "colorCodes.h"

int main() {
    char * cwd = malloc(1024);
	setbuf(stdout, NULL);
    bzero(cwd,1024);
    cwd = getcwd(cwd, 1024);
    if(cwd == NULL){
        printf(COLOR_COMMAND"getcwd()"COLOR_MESSAGE" failed"COLOR_RESET"\n");
        free(cwd);
        exit(1);
    }
    printf(COLOR_MESSAGE"\nCurrent working directory: "COLOR_RESET"%s \n", cwd);
    char go_up [] = "cd ..";
    char go_back[1027];
    char go_root [] = "cd /";
    char go_to_non_existent [] = "cd /non-existing-directory";

    bzero(go_back,1027);
    strcpy(go_back, "cd ");
    strcat(go_back, cwd);
    printf("\n\t"COLOR_POINTS"1P if next three directory changes work"COLOR_RESET"\n");
    printf("\n"COLOR_MESSAGE"Go up:"COLOR_RESET"\n %s \n" , go_up);
    execute_command(go_up);
    bzero(cwd,1024);
    cwd = getcwd(cwd, 1024);
    printf("\n"COLOR_MESSAGE"Current working directory: "COLOR_RESET"%s \n", cwd);

    printf("\n"COLOR_MESSAGE"Go to root:"COLOR_RESET"\n %s\n", go_root);
    execute_command(go_root);
    bzero(cwd,1024);
    cwd = getcwd(cwd, 1024);
    printf("\n"COLOR_MESSAGE"Current working directory: "COLOR_RESET"%s \n", cwd);

    printf("\n"COLOR_MESSAGE"Go back:"COLOR_RESET"\n %s\n", go_back);
    execute_command(go_back);
    bzero(cwd,1024);
    cwd = getcwd(cwd, 1024);
    printf("\n"COLOR_MESSAGE"Current working directory: "COLOR_RESET"%s \n", cwd);

    printf("\n\t"COLOR_POINTS"1P if error is shown and handled correctly"COLOR_RESET"\n");
    printf("\n"COLOR_MESSAGE"Trying to change into non-existent directory:"COLOR_RESET"\n %s\n"COLOR_BOLD_RED, go_to_non_existent);
    execute_command(go_to_non_existent);
    bzero(cwd,1024);
    cwd = getcwd(cwd, 1024);
    printf(COLOR_RESET"\n"COLOR_MESSAGE"Current working directory: "COLOR_RESET"%s \n", cwd);
    free(cwd);
}
