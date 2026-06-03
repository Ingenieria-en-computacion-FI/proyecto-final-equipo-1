#include <stdlib.h>
#include "linked_list.h"

struct NodeLL {
    int pid;
    struct NodeLL* next;
};

struct LinkedList {
    struct NodeLL* head;
    struct NodeLL* tail;
};

LinkedList* ll_create() {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

void ll_insert_last(LinkedList* list, int pid) {
    if (list == NULL) return;
    struct NodeLL* new_node = malloc(sizeof(struct NodeLL));
    if (new_node == NULL) return;
    
    new_node->pid = pid;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void ll_destroy(LinkedList* list) {
    if (list == NULL) return;
    struct NodeLL* current = list->head;
    while (current != NULL) {
        struct NodeLL* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}