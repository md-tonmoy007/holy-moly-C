#include "Queue.h"

void push(int data, struct Queue* queue)
{
    queue->list.insert(queue->list.length, data, &queue->list);
}

int pop(struct Queue* queue)
{
    int data = *(int*)queue->list.retrieve(0, &queue->list);
    queue->list.remove(0, &queue->list);
    return data;
}


struct Queue queue_int_constructor()
{
    struct Queue queue;
    queue.list = linked_list_constructor();
    
    queue.push = push;
    queue.pop = pop;

    return queue;
}



