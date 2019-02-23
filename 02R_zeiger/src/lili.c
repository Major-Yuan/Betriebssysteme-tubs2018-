#include <stdlib.h>
#include <stdio.h>
#include "lili.h"

element_t *head = NULL;

//implement necessary functions here
//p1 is used to describe the first element, p2 the next
element_t *p1 = NULL;
element_t *p2 = NULL;
unsigned int* insert_element(unsigned int value){
    // if the list is empty, then create a new list and set the head
    if(head == NULL){
        p1 = head = (element_t *)malloc(sizeof (element_t));
        if(head == NULL){
            perror("allocation failed");
            return NULL;
        }
        p1->data = value;
        p1->next = NULL;
    }
    else{ 
        p2 = p1->next = (element_t *)malloc(sizeof (element_t));
        p2->data = value;
        p2->next = NULL;
        p1 = p2;
    }
    unsigned int *value_pointer = &(p1->data);
    return value_pointer;
}

unsigned int remove_element(void){
    if(head == NULL){
        printf("WARNING: nothing to remove, lili is empty\n");
        return 0;
    }
    unsigned int element_removed = head->data;
    element_t *head_temp = head->next;
    free(head);
    head = head_temp;
    return element_removed;
}

void print_lili(void){
    element_t *p_print = head;
    printf("print lili: ");
    while(p_print != NULL){
        printf("%d, ",p_print->data);
        p_print = p_print->next;
    }
    printf("\n");
}
