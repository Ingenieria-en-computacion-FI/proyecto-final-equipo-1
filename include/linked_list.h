#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList LinkedList;

LinkedList* ll_create();
void ll_insert_last(LinkedList* list, int pid);
void ll_destroy(LinkedList* list);

#endif