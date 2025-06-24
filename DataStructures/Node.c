#include "Node.h"
#include <stddef.h>
#include <stdio.h>



struct Node* node_Constructor(void* data, int data_type, int size)
{

    if (size < 1 ){
        printf("Error: Size must be greater than 0.\n");
        exit(1);
    }
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (!node) {
        printf("Error: Memory allocation failed for Node.\n");
        exit(1);
    }

    switch (data_type) {
        case INT:
            node->data = malloc(sizeof(int)* size);
            for (int i=0; i < size; i++) {
                ((int*)node->data)[i] = ((int*)data)[i];
            }
            break;
        case FLOAT:
            node->data = malloc(sizeof(float) * size);
            for (int i = 0; i < size; i++) {
            ((float*)node->data)[i] = ((float*)data)[i];
            }
            break;
        case DOUBLE:
            node->data = malloc(sizeof(double) * size);
            for (int i = 0; i < size; i++) {
            ((double*)node->data)[i] = ((double*)data)[i];
            }
            break;
        case CHAR:
            node->data = malloc(sizeof(char) * size);
            for (int i = 0; i < size; i++) {
            ((char*)node->data)[i] = ((char*)data)[i];
            }
            break;
        case Bool:
            node->data = malloc(sizeof(int) * size); // Assuming Bool is represented as int
            for (int i = 0; i < size; i++) {
            ((int*)node->data)[i] = ((int*)data)[i];
            }
            break;
        default:
            printf("Error: Unknown data type.\n");
            free(node);
            exit(1);
    }
    node->size = size;
    node->next = NULL;
    return node;
}




