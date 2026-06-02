#include <stdlib.h>
#include "queue.h"

struct Node {
    int value;
    struct Node* next;
};

struct Queue {
    struct Node* front; // Por donde salen (head)
    struct Node* rear;  // Por donde entran (tail)
};

// O(1) - Inicializa la cola vacía
Queue* queue_create() {
    Queue* q = malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = NULL;
        q->rear = NULL;
    }
    return q;
}

// O(1) - Inserta un elemento al final de la fila (rear)
void enqueue(Queue* q, int value) {
    if (q == NULL) return;

    struct Node* nuevo_nodo = malloc(sizeof(struct Node));
    if (nuevo_nodo == NULL) return;

    nuevo_nodo->value = value;
    nuevo_nodo->next = NULL; // Como es el último, no tiene a nadie detrás

    if (queue_is_empty(q)) {
        // Si la fila estaba vacía, el nuevo es el primero y el último a la vez
        q->front = nuevo_nodo;
        q->rear = nuevo_nodo;
    } else {
        // Conectamos el último actual con el nuevo, y actualizamos el puntero rear
        q->rear->next = nuevo_nodo;
        q->rear = nuevo_nodo;
    }
}

// O(1) - Saca y retorna el elemento del frente de la fila (front)
int dequeue(Queue* q) {
    if (queue_is_empty(q)) return -1;

    struct Node* nodo_a_borrar = q->front;
    int valor = nodo_a_borrar->value;

    // Movemos el frente al siguiente en la fila
    q->front = q->front->next;

    // Si al sacar a la persona, la fila se quedó vacía, debemos limpiar el rear
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(nodo_a_borrar); // Liberamos memoria (Memory Leak evitado)
    return valor;
}

// O(1) - Verifica si la cola está vacía
int queue_is_empty(Queue* q) {
    if (q == NULL || q->front == NULL) {
        return 1;
    }
    return 0;
}

// O(n) - Vaciamos la cola para devolverle la RAM al sistema
void queue_destroy(Queue *q) {
    if (q == NULL) return;

    while (!queue_is_empty(q)) {
        dequeue(q);
    }
    free(q);
}
