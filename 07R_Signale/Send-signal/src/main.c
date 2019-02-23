#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void print_usage(const char* executable)
{
    fprintf(stderr, "USAGE: %s -s SIGNAL -p PID\n", executable);
    exit(EXIT_FAILURE);
}


int main (int argc, char* argv[])
{
    int cm;
    int sig_Number;
    int pid;
    printf("1");
    if(argc !=5)        // check the number of parameters 1 + 4
    {
        print_usage(argv[0]);
    }
    while((cm = getopt(argc, argv, "p:s:")) !=-1)  // get variables
    {
        printf("2");
        switch(cm)
        {
            case 'p':
                sig_Number = atoi(optarg);
                break;
            case 's':
                pid = atoi(optarg);
                break;
            //case '?':
               // print_usage(argv[0]);
               //break;
            default :
                print_usage(argv[0]);
                break;
        }
    }
    kill(pid, sig_Number);

    //write your code here
    //(void) argc; //please delete
    //(void) argv; //please delete
	return EXIT_SUCCESS;
}
