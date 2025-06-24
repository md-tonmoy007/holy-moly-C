#ifndef Queue_h
#define Queue_h



#include "LinkedList.h"

struct Queue
{
    /* data */
    struct LinkedList list;

    void (*push) (int data, struct Queue* queue);
    int (*pop) (struct Queue* queue);
    // int (*peek) (struct Queue* queue);
    // int (*is_empty) (struct Queue* queue);
};

struct Queue queue_constructor(void);




#endif