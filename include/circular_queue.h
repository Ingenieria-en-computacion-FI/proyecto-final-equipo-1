#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

typedef struct CircularQueue CircularQueue;

CircularQueue* cq_create(int capacity);

void cq_enqueue(CircularQueue *q, int value);

void cq_dequeue(CircularQueue *q);

int cq_is_empty(CircularQueue *q);

int cq_is_full(CircularQueue *q);

void cq_destroy(CircularQueue *q);


#endif