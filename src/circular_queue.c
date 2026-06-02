#include <stdlib.h>
#include "circular_queue.h"

struct CircularQueue {
    int* data;      // El arreglo que guarda los datos
    int front;      // Índice del elemento que saldrá
    int rear;       // Índice donde se insertará el nuevo elemento
    int size;       // Cuántos elementos hay actualmente
    int capacity;   // Capacidad máxima del arreglo
};

// O(1) - Crea el arreglo y prepara los índices
CircularQueue* cq_create(int capacity) {
    CircularQueue* q = malloc(sizeof(CircularQueue));
    if (q == NULL) return NULL;

    q->data = malloc(sizeof(int) * capacity);
    if (q->data == NULL) {
        free(q);
        return NULL;
    }

    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = capacity;

    return q;
}

// O(1) - Inserta dando la vuelta si es necesario
void cq_enqueue(CircularQueue *q, int value) {
    if (q == NULL || cq_is_full(q)) return; // No insertamos si está llena

    q->data[q->rear] = value;
    
    // Aquí está la magia: si rear llega al final, el módulo lo regresa a 0
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

// O(1) - Saca un elemento dando la vuelta si es necesario
int cq_dequeue(CircularQueue *q) {
    if (q == NULL || cq_is_empty(q)) return -1;

    int valor = q->data[q->front];
    
    // Avanzamos el frente. Si llega al final, regresa a 0
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return valor;
}

// O(1) - Evaluamos el contador de tamaño
int cq_is_empty(CircularQueue *q) {
    if (q == NULL) return 1;
    return q->size == 0;
}

// O(1) - Evaluamos si el tamaño alcanzó la capacidad máxima
int cq_is_full(CircularQueue *q) {
    if (q == NULL) return 0;
    return q->size == q->capacity;
}

// O(1) - Liberamos el arreglo interno y luego la estructura
void cq_destroy(CircularQueue *q) {
    if (q == NULL) return;
    
    if (q->data != NULL) {
        free(q->data);
    }
    free(q);
}


