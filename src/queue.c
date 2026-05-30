#include <stdlib.h>
#include "queue.h"

struct Node {
    int value;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

Queue* queue_create() {

    
//Implementar

    return NULL;
}

void enqueue(Queue* q, int value){

//Implementar

}

int dequeue(Queue* q){
//Implementar

    return -1;
}

int queue_is_empty(Queue* q){

//Implementar

    return 1;
}

void queue_destroy(Queue *q){

//Implementar

}