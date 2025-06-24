#ifndef LinkedList_c
#define LinkedList_c

#include<stdio.h>
#include "Node.h"



struct LinkedList
{
    /* data */
    struct Node* head;
    int length;

    void (*insert) (int index, void* data, struct LinkedList* linked_list);
    void (*remove) (int index, struct LinkedList* linked_list);
    void* (*retrieve) (int index, struct LinkedList* linked_list);
};

struct LinkedList linked_list_constructor();



#endif