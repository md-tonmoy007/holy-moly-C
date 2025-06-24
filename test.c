#include <stdio.h>
#include "DataStructures/LinkedList.h"
#include <stdlib.h>


int main()
{
    struct LinkedList list = linked_list_constructor();

    for (int i = 0; i < 10; i++)
    {
        int *x = (int*)malloc(sizeof(int));
        *x = i;
        list.insert(i, x, &list);
    }
    
    list.remove(2, &list);
    list.remove(4, &list);

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", *(int*)list.retrieve(i, &list));
    }

}