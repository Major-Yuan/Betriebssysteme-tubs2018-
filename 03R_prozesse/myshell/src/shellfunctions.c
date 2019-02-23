#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "plist.h"
#include "shellfunctions.h"
#include "shellutils.h"

// write your local helper functions here


/**
 * @brief read_input record the input
 * @param command_line pointer for input
 * @param size         size of input
 * @param stream       file pointer
 */
void read_input(char* const command_line, int size, FILE* stream)
{
    // Write your code here
    prompt();
    if(fgets(command_line, size, stream) ==NULL){
        if(feof(stream)) {
            puts("\n");
            printf("Goodbey!\n");
            exit(3);
        }

    }
// delete the following lines if you are implementing this function
//    (void)command_line; //mark command_line used for the compiler
//    (void)size;         //mark size used for the compiler
//    (void)stream;       //mark stream used for the compiler

}


/**
 * @brief execute_command parent/child process and path change
 * @param command_line    input pointer
 */
void execute_command(char* command_line)
{
    // Write your code here
    command_t *command = parse_command_line(command_line);
    if(command->parse_error != NULL){
        perror("error");
        exit(3);
    }
    if(command == NULL){
        perror("command allocation failed");
        exit(3);
    }
    if(command->argv[0] == '\0'){
        perror("the first letter shouldn't be empty");
        exit(3);
    }

    //build a child process
    pid_t pid = fork();
    int status = 0;

    //printf("background is: %d",command->background);
    if(pid < 0) {
        perror("set kind process not success");
        exit(3);
    } else if (pid==0) {  //in child process
        execvp(command->argv[0], command->argv);
        //test what is argv[0] and what is argv
        //printf("argv[0] is: %s", command->argv[0]);
        //printf("argv is: %s", *command->argv);
    } else {
        if(command->background == 1){
            insert_element(pid,command->command_line);
        } else{
            if(waitpid(pid, &status ,0) == -1){
                perror("waitpid failed");
                exit(3);
             }
        }
        print_status(command_line,status);
    }
    // Path change
    char *aa = " ";
    char *p = strtok(command->command_line, aa); //get the string before " "
    printf("%s",p);
    if(strcmp(p, "cd") == 0){
        p = strtok(NULL, aa);  //get the string after " "
        if(chdir(command->argv[1]) == -1){
            perror("Path is not correct");
            exit(3);
        } else{
            chdir(p);
        }
    }
    free(command);
}

/**
 * @brief collect_defunct_process Zombieprocess collect 
 */
void collect_defunct_process()
{
    int status;
    pid_t pid;
    while((pid = waitpid(-1,&status,WNOHANG)) > 0){
        char buffer[50];
        remove_element(pid,buffer,strlen(buffer));
        printf("removed cmd is: %s\n", buffer);
    }
}
