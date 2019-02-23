/*
    Auagabe 11 von Jicheng Yuan und Zhengyang Li
*/
#include "reads_list.h"
#include "pthread.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct reads_list_element
{
    //! HINT: something is missing here
    unsigned int    client_number;
    struct reads_list_element* next;
    struct reads_list_element* previous;
    sem_t sem1;

} reads_list_element_t;


reads_list_element_t* head = NULL;

//! HINT: maybe global synchronization variables are needed
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
reads_list_element_t* now = NULL;

//-----------------------------------------------------------------------------

int reads_list_insert_element(unsigned int client_number)
{
    //! HINT: synchronization is needed in this function

    //! create new element
    reads_list_element_t* new_element = malloc(sizeof(reads_list_element_t));
    if(new_element == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_element->client_number = client_number;

    // signal init
    sem_init(&new_element -> sem1,0,0);
    //locking
    pthread_mutex_lock(&mutex);

    //! insert element into list
    if(head == NULL)
    {
        new_element->next     = NULL;
        new_element->previous = NULL;
        head                  = new_element;
        //unlocking
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    reads_list_element_t* temporary = head;
    while(temporary->next != NULL)
    {
        temporary = temporary->next;
    }
    new_element->next     = NULL;
    new_element->previous = temporary;
    temporary->next       = new_element;
    //unlocking
    pthread_mutex_unlock(&mutex);
    return 0;
}

//-----------------------------------------------------------------------------

sem_t* reads_list_get_reader_semaphore(unsigned int client_number)
{
    //(void) client_number; //! Please remove this when you implement this function
    //! please implement this function
    // locking
    pthread_mutex_lock(&mutex);
    reads_list_element_t* temp = head;
    while (temp != NULL && temp->client_number != client_number)
    {
       temp = temp->next;
    }
    //unlocking
    pthread_mutex_unlock(&mutex);
    printf("hier ist out reads_list_get_reader_semaphore\n");
    return &(temp->sem1); //! Please select a proper return value
}

//-----------------------------------------------------------------------------

void reads_list_increment_all()
{
    //! HINT: synchronization is needed in this function
    //  locking
    pthread_mutex_lock(&mutex);
    reads_list_element_t* temporary = head;
    while(temporary != NULL)
    {
        sem_post(&temporary -> sem1);
        temporary = temporary->next;
    }
    // unlocking
    pthread_mutex_unlock(&mutex);
}

//-----------------------------------------------------------------------------

void reads_list_decrement(unsigned int client_number)
{


    (void) client_number; //! Please remove this when you implement this function
    //! please implement this function
    sem_wait(reads_list_get_reader_semaphore(client_number));
}

//-----------------------------------------------------------------------------

int reads_list_remove_reader(unsigned int client_number)
{
    //! HINT: synchronization is needed in this function

    //! find element to remove
    reads_list_element_t* temporary = head;
    while(temporary != NULL && temporary->client_number != client_number)
    {
        temporary = temporary->next;
    }

    if(temporary == NULL)
    {
        return -1;
    }
    //locking
    pthread_mutex_lock(&mutex);
    //! bend pointers around element
    if(temporary->previous != NULL)
    {
        temporary->previous->next = temporary->next;
    }
    if(temporary->next != NULL)
    {
        temporary->next->previous = temporary->previous;
    }
    if(temporary == head)
    {
        head = temporary->next;
    }
    // unlocking
    pthread_mutex_unlock(&mutex);
    //! finally delete element
    free(temporary);
    return 0;
}

//-----------------------------------------------------------------------------

int reads_list_get_reads(unsigned int client_number)
{
    int buffer = 0;

    //(void) client_number; //! Please remove this when you implement this function
    //! please implement this function
    sem_getvalue(reads_list_get_reader_semaphore(client_number), &buffer);

    return buffer;
}
