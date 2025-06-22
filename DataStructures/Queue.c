#include "Queue.h"

void push(int data, struct Queue_int* queue)
{
    queue->list.insert(queue->list.length, data, &queue->list);
}

int pop(struct Queue_int* queue)
{
    if (queue->list.length == 0) {
        return; // or handle underflow
    }
    int data = queue->list.retrieve(0, &queue->list);
    queue->list.remove(0, &queue->list);
    return data;
}


struct Queue_int queue_int_constructor()
{
    struct Queue_int queue;
    queue.list = linked_list_int_constructor();
    
    queue.push = push;
    queue.pop = pop;

}



