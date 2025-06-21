#include "LinkedList.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct Node_int *create_node_int(int data);
void destroy_node_int(struct Node_int* node);
struct Node_int* iterate_int(int index, struct LinkedList_int* list);
void insert_node_int(int index, int data, struct LinkedList_int* linked_list);
void remove_node_int(int index, struct LinkedList_int* linked_list);
int retrieve_data_int(int index, struct LinkedList_int* linked_list);


struct LinkedList_int linked_list_int_constructor(){
    struct LinkedList_int new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_node_int;
    new_list.remove = remove_node_int;
    new_list.retrieve = retrieve_data_int;

    return new_list;
}

struct Node_int *create_node_int(int data) {
    struct Node_int* new_node = (struct Node_int*)malloc(sizeof(struct Node_int));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void destroy_node_int(struct Node_int* node_to_destroy) {
    if (node_to_destroy != NULL) {
        free(node_to_destroy);
    }
}

struct Node_int* iterate_int(int index, struct LinkedList_int* linked_list) {
    if (index < 0 || index >= linked_list->length) {
        fprintf(stderr, "Error: Index out of bounds (%d) for list of length %d\n", index, linked_list->length);
        exit(9);
    }

    struct Node_int* cursor = linked_list->head;
    for (int i = 0; i < index; i++) {
        if (cursor == NULL) {
            fprintf(stderr, "Error: Unexpected NULL cursor during iteration at index %d\n", i);
            exit(9);
        }
        cursor = cursor->next;
    }
    return cursor;
}


void insert_node_int(int index, int data, struct LinkedList_int *linked_list)
{
    if (index < 0 || index > linked_list->length) {
        fprintf(stderr, "Error: Insertion index out of bounds (%d) for list of length %d.\n", index, linked_list->length);
        exit(9);
    }

    struct Node_int* node_to_insert = create_node_int(data);

    if (index == 0) {
        node_to_insert->next = linked_list->head;
        linked_list->head = node_to_insert;
    } else {
        struct Node_int *cursor = iterate_int(index - 1, linked_list);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }
    linked_list->length++;
}

void remove_node_int(int index, struct LinkedList_int *linked_list)
{
    if (index < 0 || index >= linked_list->length) {
        fprintf(stderr, "Error: Removal index out of bounds (%d) for list of length %d.\n", index, linked_list->length);
        return;
    }

    struct Node_int *node_to_remove = NULL;

    if (index == 0) {
        node_to_remove = linked_list->head;
        if (node_to_remove != NULL) {
            linked_list->head = node_to_remove->next;
        } else {
            return;
        }
    }
    else {
        struct Node_int *prev_node = iterate_int(index - 1, linked_list);

        if (prev_node != NULL && prev_node->next != NULL) {
            node_to_remove = prev_node->next;
            prev_node->next = node_to_remove->next;
        } else {
            fprintf(stderr, "Error: Internal logic issue during remove_node_int at index %d.\n", index);
            return;
        }
    }

    destroy_node_int(node_to_remove);
    linked_list->length--;
}

int retrieve_data_int(int index, struct LinkedList_int *linked_list)
{
    struct Node_int *cursor = iterate_int(index, linked_list);
    return cursor->data;
}
