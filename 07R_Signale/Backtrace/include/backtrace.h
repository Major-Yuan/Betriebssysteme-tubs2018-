#ifndef _BACKTRACE_H_
#define _BACKTRACE_H_

#define MAXIMAL_BACKTRACE_DEPTH 32

/**
 * prints a backtrace of called functions 
 */
void print_backtrace(void);


/**
 * prints a signal number and calls backtrace
 * @param signal_number: the signal number
 */
void signal_handler(int signal_number);


/**
 * registers a custom signal handler for some signals
 * in order to override the default behaviour
 */
void initialize_signal_handler(void);

#endif
