#include <stdio.h>
#include <unistd.h>   //for sleep()   
#include <time.h>     //for time()
#include <stdlib.h>   //for rand()
#include "backtrace.h"

#define PRINT_ERROR printf("ERROR in %i:%s in function %s\n", __LINE__, __FILE__, __FUNCTION__)

static unsigned int tick_counter = 0;


/**
 * print tick and sleep
 */
void tick_one(void)
{
	printf("tick %3d\n", ++tick_counter);
	sleep(2);
		// time_t time_stamp = time(NULL);
		// while (time_stamp+2 <= time(NULL));	
}


/**
 * print tick and sleep
 */
void tick_two(void)
{
	printf("tick %3d\n", ++tick_counter);
	sleep(2);
}


/**
 * print tick and sleep
 */
void tick_three(void) 
{
	printf("tick %3d\n", ++tick_counter);
	sleep(2);
}


/**
 * call randomly one of the tick functions
 */
void decision_maker(void)
{
	unsigned int random = rand() % 3; 

	switch (random)
	{
		case 0:
			tick_one();
			break;
		case 1:
			tick_two();
			break;
		case 2:
			tick_three();
			break;
		default:
			PRINT_ERROR;
			break;
	}
}



int main() 
{
	printf("Compiled on %s, %s\n\n", __DATE__, __TIME__);

	initialize_signal_handler();
	srand(time(NULL)); //generate random seed

	while(1)
	{
		decision_maker();
	}

}
