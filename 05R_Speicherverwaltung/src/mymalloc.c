#include "mymalloc.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colorCodes.h"

chunk_t* root = NULL;

//===================================================================================================================//

//! --------------------------------
//! Write your helper functions here
//! --------------------------------
/**
 * @brief append
 * @param last
 * @param size
 */
void append(memory_block_t *last, size_t size){
    memory_block_t *temp = last + size / sizeof (memory_block_t) + 1;
    temp->previous = last->previous;
    if (last->previous != NULL) {
        last->previous->next = temp;
    }
    else {
        root->free_space_list_entry_point = temp;
    }
    temp->next = NULL;
    temp->size = last->size - size - sizeof (memory_block_t);
}

/**
 * @brief delete_Memory
 * @param freeMemory
 */
void delete_Memory(memory_block_t *freeMemory){
    if (freeMemory->previous == NULL){
        root->free_space_list_entry_point = freeMemory->next;
    }
    else {
        if (freeMemory->next == NULL){
            freeMemory->previous->next = NULL;
        }
        else {
            freeMemory->previous->next = freeMemory->next;
            freeMemory->next->previous = freeMemory->previous;
        }
    }
}

/**
 * @brief insert
 * @param freeMemory
 * @param size
 */
void insert (memory_block_t *freeMemory, size_t size){
    memory_block_t *temp = freeMemory + size / sizeof (memory_block_t) + 1;
    temp->previous = freeMemory->previous;
    if (freeMemory->previous != NULL) {
        freeMemory->previous->next = temp;
    }
    else {
        root->free_space_list_entry_point = temp;
    }
    temp->next = freeMemory->next;
    freeMemory->next->previous = temp;
    temp->size = freeMemory->size - size - sizeof (memory_block_t);
}

/**
 * @brief free_at_center
 * @param pointer
 */
void free_at_center(memory_block_t* pointer){
    memory_block_t *temp = root->free_space_list_entry_point;
    while(temp < pointer){
        temp = temp->next;
    }
    temp->previous->next = pointer;
    pointer->previous = temp->previous;
    pointer->next = temp;
    temp->previous = pointer;
}

/**
 * @brief free_at_first
 * @param pointer
 */
//FB pointer->previous wird auf MAGIC gelassen
void free_at_first(memory_block_t *pointer) {
    pointer->previous = NULL;
    pointer->next = root->free_space_list_entry_point;
    root->free_space_list_entry_point->previous = pointer;
    root->free_space_list_entry_point = pointer;
}

/**
 * @brief free_at_last
 * @param last
 * @param pointer
 */
void free_at_last(memory_block_t * last, memory_block_t *pointer){
    last->next = pointer;
    pointer->previous = last;
    pointer->next = NULL;
}

/**
 * @brief if_merge
 * @return
 */
memory_block_t *if_merge(){
    memory_block_t *temp = root->free_space_list_entry_point;
    while(temp->next != NULL){
        if((temp + temp->size / sizeof (memory_block_t) + 1 ) == temp->next ){
            return temp;
        }
        else {
            temp = temp->next;
        }
    }
    return NULL;
}

/**
 * @brief merge_free_memory
 */
void merge_free_memory(){
    memory_block_t *temp = if_merge();
    while(temp != NULL) {
        temp->size = temp->size + temp->next->size + sizeof (memory_block_t);
        if (temp->next->next != NULL){
            temp->next->next->previous = temp;
            temp->next = temp->next->next;
        }
        else {
            temp->next = NULL;
        }
        temp = if_merge();
    }
}

/**
 * @brief if_right_adress
 * @param memoryLocation
 * @return
 */
int if_right_adress(void *memoryLocation){
    if ((void*) memoryLocation > (void*) root
            && memoryLocation < (void*) (root + root->size / sizeof (memory_block_t))) {
        int temp = 1;
        while ((void*) (root + temp) < memoryLocation && temp < (int)( root->size / sizeof (memory_block_t) )) {
            temp++;
            if( (void*)(root + temp) == memoryLocation ) {
                return 1;
            }
        }
    }
    return 0;
}
//===================================================================================================================//

/**
 * @brief get_page_size returns page size in bytes
 * @return page size in byte
 */
size_t get_page_size(void)
{
    // get the size of a page in bytes
    return sysconf(_SC_PAGESIZE);
}

//-------------------------------------------------------------------------------------------------------------------//

/**
 * @brief open_file: opens a file with the size of 1 page for that we want to manage the memory
 * @return file descriptor
 */
int open_file(void)
{
    // 1. open the file, if not exist, create a file (O_CREAT)
    // 2. this file can be written and read (O_RDWR)
    // 3. if a new file is created, then it has write and read permission (S_IRUSR | S_IWUSR)
    int fileDescriptor = open(FILE_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    // if the file is not opened successfully
    if (fileDescriptor == -1){
        perror("failed to open file");
        exit(-1);
    }

    // offset is 0, and use get_page_size to get the size of the page
    int ifFail = posix_fallocate(fileDescriptor, 0, get_page_size());
    // return 0, if success
    if(ifFail != 0){
        fprintf(stderr, "falied to locate"); // small fix
        exit(-1);
    }

    // 1. (PROT_READ | PROT_WRITE) pages may be written and read
    void* address = mmap(START_ADDRESS, 4096, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, fileDescriptor, 0);
    // if success, return the poiter of this mapped area.
    // if map failed, return MAP_FAILED
    if(address == MAP_FAILED) {
        perror("map failed");
        exit(-1);
    }

    int *temp = address;
    // clear the memory in this area
    for(unsigned int i = 0; i < 4096 / sizeof (int); i++){
        *(temp++) = 0;
    }

    root = (chunk_t*) address;
    root->size = get_page_size(); // size of the root
    root->file = fileDescriptor; // file of the root
    memory_block_t *first = (memory_block_t*) (root + 1); // the first memory block
    first->size = root->size - 2 * sizeof (memory_block_t); // size of root and first memory block need 2 memory_block_t
    first->previous = NULL;
    first->next = NULL;
    root->free_space_list_entry_point = first;

    return fileDescriptor;
}

//-------------------------------------------------------------------------------------------------------------------//

/**
 * @brief my_malloc allocates memory that is backed by a file
 * @param size: size of memory to allocate in bytes
 * @return pointer to allocated memory
 */
void* my_malloc(size_t size)
{
    //FB Hier sollte geprüft werden, ob das root Element existiert, anstatt sich darauf zu verlassen, dass es open_file() in main.c aufgerufen wird.
    if(!root) {
        exit(1);
    }
    size--;
    size /= sizeof (memory_block_t);
    size++;
    size *= sizeof (memory_block_t);
    memory_block_t *allocated = NULL;
    memory_block_t *freeMemory = root->free_space_list_entry_point;
    while(freeMemory != NULL) {
        if(freeMemory->size > size) {
            if(freeMemory->next == NULL) {
                append(freeMemory, size);
            }
            else {
                insert(freeMemory,size);
            }
            allocated = freeMemory;
            allocated->size = size;
            allocated->previous = MAGIC_NUMBER;
            allocated->next = MAGIC_NUMBER;
            break;
        }
        else if (freeMemory->size == size){
            delete_Memory(freeMemory);
            allocated = freeMemory;
            allocated->size = freeMemory->size;
            allocated->previous = MAGIC_NUMBER;
            allocated->next = MAGIC_NUMBER;
            break;
        }
        else {
            freeMemory = freeMemory->next;
        }
    }
    if(allocated == NULL){
        errno = ENOMEM;
        return NULL;
    }

    return (allocated + 1);
    /*(void)size;  // remove this line before implementation of this function
                 // put your code here...
    return NULL; // remove this line before implementation of this function */
}

//-------------------------------------------------------------------------------------------------------------------//

/**
 * @brief my_free: releases memory that was allocated by my_free
 * @param memory_location: pointer to memory that should be freed
 */
void my_free(void* memory_location)
{
    if(if_right_adress(memory_location) == 1) {
        memory_block_t* pointer = (memory_block_t*) memory_location - 1;

        if(pointer->next == MAGIC_NUMBER && pointer->previous == MAGIC_NUMBER && root != NULL) {
            memory_block_t *last = root->free_space_list_entry_point;
            while(last->next != NULL) {
                last = last->next;
            }
            if (pointer < root->free_space_list_entry_point){
                free_at_first(pointer);
            }
            else if (pointer < last) {
                free_at_center(pointer);
            }
            else{
                free_at_last(last,pointer);
            }
            merge_free_memory();
        }
    }
    else {
        printf("uncorrect address!");
    }
    //(void)memory_location; // remove this line before implementation of this function
    // put your code here...
}

