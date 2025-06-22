#ifndef Queue_h
#define Queue_h



#include "LinkedList.h"

struct Queue_int
{
    /* data */
    struct LinkedList_int list;

    void (*push) (int data, struct Queue_int* queue);
    int (*pop) (struct Queue_int* queue);
    // int (*peek) (struct Queue_int* queue);
    // int (*is_empty) (struct Queue_int* queue);
};

Queue_int queue_int_constructor(void);




#endif