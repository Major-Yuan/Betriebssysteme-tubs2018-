#include "backtrace.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "execinfo.h"

//-----------------------------------------------------------------------------
void print_backtrace(void)
{
    void *array[10];
    int size = 0;
    char **strings = NULL;
    int i = 0;
    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size);
    //if(strings != NULL)
    for(i = 0; i < size; i++)
    {
        printf("%s\n",strings[i]);
    }
    free(strings);
    strings = NULL;
}

//-----------------------------------------------------------------------------

void signal_handler(int sig)
{
    int sig_Number = sig;
    printf("Now the singal number is %d\n",sig_Number);
    print_backtrace();
    exit(sig_Number);
}

//-----------------------------------------------------------------------------

void initialize_signal_handler(void)
{
    signal(SIGINT, signal_handler);     // Interrupt from keyboard
    signal(SIGQUIT, signal_handler);    // Quit from keyboard
    signal(SIGILL, signal_handler);     // Illegal Instruction
    signal(SIGTERM, signal_handler);    // Termination
    signal(SIGSTOP, signal_handler);    // Stop process
    signal(SIGFPE, signal_handler);     // Floating point exception
    signal(SIGSEGV, signal_handler);    // Invalid memory reference

}
