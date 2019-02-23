#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plist.h"
#include "shellutils.h"
#include "shellfunctions.h"
#include "shellfunctions_helper.h"
#include "colorCodes.h"

int main() {
    char jobs  [] = "jobs";
    char sleep_background1 [] = "sleep 4 &";
    char sleep_background2 [] = "sleep 4 &";
    char sleep_background3 [] = "sleep 4 &";
    char sleep_background4 [] = "sleep 4 &";
    printf("\n\t"COLOR_POINTS"1P"COLOR_RESET"\n");
    printf("\n"COLOR_MESSAGE"Testing \""COLOR_COMMAND"walk_list"COLOR_MESSAGE"\" now, it should print a list of two sleep jobs running in the background:"COLOR_RESET"\n");
    sleep(1);
    execute_command(sleep_background1);
    execute_command(sleep_background2);
    walk_list (print_job);
    printf("\n\t"COLOR_POINTS"1P"COLOR_RESET"\n");
    printf("\n\""COLOR_COMMAND"jobs"COLOR_MESSAGE"\" should come directly showing serveral \""COLOR_COMMAND"sleep"COLOR_MESSAGE"\" processes:"COLOR_RESET"\n");
    sleep(1);
    execute_command(sleep_background3);
    execute_command(sleep_background4);
    execute_command(jobs);
    sleep(5);
    printf("\n\t"COLOR_POINTS"1P"COLOR_RESET"\n");
    printf("\n"COLOR_MESSAGE"Testing \""COLOR_COMMAND"walk_list"COLOR_MESSAGE"\" now with no elements, it should hopefully not crash\n Only exit status expected:"COLOR_RESET"\n");
    collect_defunct_process();
    walk_list (print_job);
}
