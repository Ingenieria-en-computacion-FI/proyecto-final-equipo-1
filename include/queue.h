#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue;

Queue* queue_create();

void enqueue(Queue *q, int value);

int dequeue(Queue *q);

int queue_is_empty(Queue *q);

void queue_destroy(Queue *q);


#endif