#ifndef LinkedList_c
#define LinkedList_c

#include<stdio.h>
#include "Node.h"



struct LinkedList_int
{
    /* data */
    struct Node_int* head;
    int length;

    void (*insert) (int index, int data, struct LinkedList_int* linked_list);
    void (*remove) (int index, struct LinkedList_int* linked_list);
    int (*retrieve) (int index, struct LinkedList_int* linked_list);
};

// struct Node_int* iterate(int index, struct LinkedList_int* list);
struct LinkedList_int linked_list_int_constructor();



#endif