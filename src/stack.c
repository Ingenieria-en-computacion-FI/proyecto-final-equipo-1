#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct Node {
    int value;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

// Esta ya venía hecha por Dylan. Reserva memoria para la estructura de la pila.
Stack* stack_create() {
    Stack* stack = malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

// O(1) - Inserta un elemento en el tope
void stack_push(Stack* stack, int value) {
    if (stack == NULL) return;

    // 1. Creamos el nuevo nodo
    struct Node* nuevo_nodo = malloc(sizeof(struct Node));
    if (nuevo_nodo == NULL) return; // Validación por si nos quedamos sin RAM

    // 2. Le asignamos el valor
    nuevo_nodo->value = value;

    // 3. Lo conectamos: su "siguiente" será el que antes era el tope
    nuevo_nodo->next = stack->top;

    // 4. Actualizamos el tope oficial de la pila
    stack->top = nuevo_nodo;
}

// O(1) - Saca y retorna el elemento del tope
int stack_pop(Stack* stack) {
    if (stack_is_empty(stack)) {
        return -1; // Retornamos -1 si intentan hacer pop a una pila vacía
    }

    // 1. Guardamos el nodo que vamos a borrar en un puntero temporal
    struct Node* nodo_a_borrar = stack->top;
    
    // 2. Extraemos su valor para no perderlo
    int valor = nodo_a_borrar->value;

    // 3. Movemos el tope al siguiente nodo de abajo
    stack->top = stack->top->next;

    // 4. Liberamos la memoria del nodo viejo para evitar fugas (Memory Leaks)
    free(nodo_a_borrar);

    return valor;
}

// O(1) - Solo mira el valor del tope sin borrarlo
int stack_peek(Stack* stack) {
    if (stack_is_empty(stack)) {
        return -1;
    }
    return stack->top->value;
}

// O(1) - Verifica si el tope es NULL
int stack_is_empty(Stack* stack) {
    if (stack == NULL || stack->top == NULL) {
        return 1; // Verdadero (está vacía)
    }
    return 0; // Falso (tiene elementos)
}

// O(n) - Destruye toda la pila para liberar memoria al cerrar el programa
void stack_destroy(Stack* stack) {
    if (stack == NULL) return;

    // Hacemos pop recursiva o iterativamente hasta vaciarla
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
    
    // Finalmente borramos la estructura principal
    free(stack);
}
