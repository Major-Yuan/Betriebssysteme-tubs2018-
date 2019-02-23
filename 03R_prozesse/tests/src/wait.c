#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    unsigned int seconds = 0;
    
    if (argc == 1) seconds = 1;
    else           seconds = atoi(argv[1]);

    sleep(seconds);  
    return 0;     
}

