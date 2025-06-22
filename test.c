#include <stdio.h>
#include "DataStructures/LinkedList.h"

#include "DataStructures/Queue.h"

int main()
{
    struct Queue_int queue = queue_int_constructor();

    for (int i = 0; i < 10; i++)
    {
        queue.push(i, &queue);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", queue.pop(&queue));
    }

}