#include "LinkedList.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct Node *create_node(void* data);
void destroy_node(struct Node* node);
struct Node* iterate(int index, struct LinkedList* list);
void insert_node(int index, void* data, struct LinkedList* linked_list);
void remove_node(int index, struct LinkedList* linked_list);
void* retrieve_data(int index, struct LinkedList* linked_list);


struct LinkedList linked_list_constructor(){
    struct LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_node;
    new_list.remove = remove_node;
    new_list.retrieve = retrieve_data;

    return new_list;
}

struct Node *create_node(void* data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void destroy_node(struct Node* node_to_destroy) {
    if (node_to_destroy != NULL) {
        free(node_to_destroy->data); // Free the data if it was dynamically allocated
        free(node_to_destroy);
    }
}

struct Node* iterate(int index, struct LinkedList* linked_list) {
    if (index < 0 || index >= linked_list->length) {
        fprintf(stderr, "Error: Index out of bounds (%d) for list of length %d\n", index, linked_list->length);
        exit(9);
    }

    struct Node* cursor = linked_list->head;
    for (int i = 0; i < index; i++) {
        if (cursor == NULL) {
            fprintf(stderr, "Error: Unexpected NULL cursor during iteration at index %d\n", i);
            exit(9);
        }
        cursor = cursor->next;
    }
    return cursor;
}


void insert_node(int index, void* data, struct LinkedList *linked_list)
{
    if (index < 0 || index > linked_list->length) {
        fprintf(stderr, "Error: Insertion index out of bounds (%d) for list of length %d.\n", index, linked_list->length);
        exit(9);
    }

    struct Node* node_to_insert = create_node(data);

    if (index == 0) {
        node_to_insert->next = linked_list->head;
        linked_list->head = node_to_insert;
    } else {
        struct Node *cursor = iterate(index - 1, linked_list);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }
    linked_list->length++;
}

void remove_node(int index, struct LinkedList *linked_list)
{
    if (index < 0 || index >= linked_list->length) {
        fprintf(stderr, "Error: Removal index out of bounds (%d) for list of length %d.\n", index, linked_list->length);
        return;
    }

    struct Node *node_to_remove = NULL;

    if (index == 0) {
        node_to_remove = linked_list->head;
        if (node_to_remove != NULL) {
            linked_list->head = node_to_remove->next;
        } else {
            return;
        }
    }
    else {
        struct Node *prev_node = iterate(index - 1, linked_list);

        if (prev_node != NULL && prev_node->next != NULL) {
            node_to_remove = prev_node->next;
            prev_node->next = node_to_remove->next;
        } else {
            fprintf(stderr, "Error: Internal logic issue during remove_node at index %d.\n", index);
            return;
        }
    }

    destroy_node(node_to_remove);
    linked_list->length--;
}

void* retrieve_data(int index, struct LinkedList *linked_list)
{
    struct Node *cursor = iterate(index, linked_list);
    return cursor->data;
}
