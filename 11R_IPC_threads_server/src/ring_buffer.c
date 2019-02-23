/*
    Auagabe 11 von Jicheng Yuan und Zhengyang Li
*/
#include "../include/ring_buffer.h"
#include "../include/reads_list.h"
#include "../include/server.h"

#include "pthread.h"
#include "semaphore.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

typedef struct ring_buffer_element
{
    //! HINT: something is missing here
    char text[MAX_MESSAGE_LENGTH];
    int             reader_count;
    pthread_mutex_t mutex_read;

} ring_buffer_element_t;


static ring_buffer_element_t ring_buffer[RINGBUFFER_SIZE];

unsigned int current_writer = 0;

unsigned int number_of_readers = 0;

//! HINT: maybe global synchronization variables are needed
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t ring_buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

//-----------------------------------------------------------------------------

int ringbuffer_write_element(char* text)
{
    //! HINTS: Check if thread can read a new element, and synchronization will be needed
    /* ... */
    if (ring_buffer[current_writer % RINGBUFFER_SIZE].reader_count != 0)
    {
        return -1;
    }
    //locking
    pthread_mutex_lock(&ring_buffer[current_writer % RINGBUFFER_SIZE].mutex_read);
    if (ring_buffer[current_writer % RINGBUFFER_SIZE].reader_count != 0) {
        pthread_cond_wait(&condition, &ring_buffer[current_writer % RINGBUFFER_SIZE].mutex_read);
    }
    //unlocking
    pthread_mutex_unlock(&ring_buffer[current_writer % RINGBUFFER_SIZE].mutex_read);
    //! Write element
    strcpy(ring_buffer[current_writer % RINGBUFFER_SIZE].text, text);

    ring_buffer[current_writer % RINGBUFFER_SIZE].reader_count = number_of_readers;

    reads_list_increment_all();

    current_writer++;

    return 0;
}

//-----------------------------------------------------------------------------

void ringbuffer_read_element(int* current_reader, char* buffer, unsigned int client_number)
{

    int reader = *current_reader;
    //! HINT: Check if thread can read a new element & synchronization will be needed
    /* ... */
    //locking
    pthread_mutex_lock(&ring_buffer[reader % RINGBUFFER_SIZE].mutex_read);
    int sem_temp;
    sem_getvalue(reads_list_get_reader_semaphore(client_number), &sem_temp);
    if (ring_buffer[reader % RINGBUFFER_SIZE].reader_count == 0 || sem_temp == 0)
    {
        strcpy(buffer, "nack");
        pthread_mutex_unlock(&ring_buffer[reader % RINGBUFFER_SIZE].mutex_read);
        return;
    }
    //locking
    pthread_mutex_unlock(&ring_buffer[reader % RINGBUFFER_SIZE].mutex_read);
    ring_buffer[reader % RINGBUFFER_SIZE].reader_count--;

    reads_list_decrement(client_number);

    //! Read Element
    strcpy(buffer, (const char*)ring_buffer[reader % RINGBUFFER_SIZE].text);

    //! HINT: notify the writer
    if (ring_buffer[reader % RINGBUFFER_SIZE].reader_count == 0)
    {
        pthread_cond_signal(&condition);
    }

    //! Update reader count
    (*current_reader)++;

    return;
}

//-----------------------------------------------------------------------------

int ringbuffer_add_reader(unsigned int client_number)
{
    //! HINT: synchronization is needed in this function

    if(reads_list_insert_element(client_number) != 0)
    {
        exit(EXIT_FAILURE);
    }
    //locking
    pthread_mutex_lock(&ring_buffer_mutex);
    number_of_readers++;
    int new_reader = current_writer;
    //unlocking
    pthread_mutex_unlock(&ring_buffer_mutex);

    return new_reader;
}

//-----------------------------------------------------------------------------

void ringbuffer_remove_reader(int* current_reader, unsigned int client_number)
{
    //! HINT: synchronization is needed in this function

    int reads = reads_list_get_reads(client_number);

    //! perform all unfinished reads for the disconnected client
    while(reads != 0)
    {
        char buffer[MAX_MESSAGE_LENGTH];
        ringbuffer_read_element(current_reader, buffer, client_number);
        reads = reads_list_get_reads(client_number);
    }
    //locking
    reads_list_remove_reader(client_number);
    pthread_mutex_lock(&ring_buffer_mutex);
    number_of_readers--;
    //unlocking
    pthread_mutex_unlock(&ring_buffer_mutex);

    return;
}
