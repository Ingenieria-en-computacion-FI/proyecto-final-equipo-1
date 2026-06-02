#include <stdlib.h>
#include "memory_manager.h"

// O(1) - Inicializa la memoria con un solo GRAN bloque libre
MemoryManager* mm_create(int total_memory) {
    MemoryManager* mm = malloc(sizeof(MemoryManager));
    if (mm == NULL) return NULL;

    MemoryBlock* block = malloc(sizeof(MemoryBlock));
    if (block == NULL) {
        free(mm);
        return NULL;
    }

    // Inicializamos el bloque gigante de memoria virgen
    block->start = 0;
    block->size = total_memory;
    block->free = 1;  // 1 = Libre, 0 = Ocupado
    block->pid = -1;  // -1 significa que nadie lo está usando
    block->next = NULL;
    block->prev = NULL;

    mm->head = block;
    mm->total_memory = total_memory;

    return mm;
}

// O(n) - FIRST FIT: Busca el primer bloque libre que sea lo suficientemente grande
int mm_allocate_first_fit(MemoryManager* mm, int size) {
    if (mm == NULL || mm->head == NULL) return -1;

    MemoryBlock* current = mm->head;

    while (current != NULL) {
        if (current->free == 1 && current->size >= size) {
            
            // Si el bloque libre es más grande de lo que necesitamos, lo "partimos" (Split)
            if (current->size > size) {
                MemoryBlock* new_block = malloc(sizeof(MemoryBlock));
                
                // El nuevo bloque libre empezará justo donde termina el que vamos a ocupar
                new_block->start = current->start + size;
                new_block->size = current->size - size;
                new_block->free = 1;
                new_block->pid = -1;
                
                // Conectamos los punteros de la lista doblemente ligada
                new_block->next = current->next;
                new_block->prev = current;
                
                if (current->next != NULL) {
                    current->next->prev = new_block;
                }
                current->next = new_block;
                
                // Reducimos el tamaño del bloque actual a lo que pidió el proceso
                current->size = size;
            }
            
            // Ocupamos el bloque actual
            current->free = 0;
            
            // TRUCO PARA EL TEST: Usaremos la dirección de inicio (start) como su ID asignado
            current->pid = current->start; 
            
            return current->start; // Retornamos en qué índice de memoria se guardó
        }
        current = current->next;
    }
    return -1; // No se encontró espacio suficiente
}

// O(n) - Libera el bloque de memoria
void mm_free(MemoryManager* mm, int pid) {
    if (mm == NULL || mm->head == NULL) return;

    MemoryBlock* current = mm->head;
    while (current != NULL) {
        // Buscamos el bloque por su identificador asignado
        if (current->free == 0 && current->pid == pid) {
            current->free = 1;
            current->pid = -1;
            
            // ¡MAGIA! Inmediatamente llamamos a la función para unir huecos
            mm_coalesce(mm);
            return;
        }
        current = current->next;
    }
}

// O(n) - COALESCENCIA: Une bloques libres que están uno al lado del otro
void mm_coalesce(MemoryManager* mm) {
    if (mm == NULL || mm->head == NULL) return;

    MemoryBlock* current = mm->head;
    while (current != NULL && current->next != NULL) {
        
        // Si el bloque actual y su vecino derecho están libres, ¡los fusionamos!
        if (current->free == 1 && current->next->free == 1) {
            MemoryBlock* block_to_delete = current->next;
            
            // El bloque actual absorbe el tamaño del vecino
            current->size += block_to_delete->size;
            
            // Desconectamos al vecino de la lista
            current->next = block_to_delete->next;
            if (block_to_delete->next != NULL) {
                block_to_delete->next->prev = current;
            }
            
            free(block_to_delete); // Borramos al vecino
            
            // IMPORTANTE: No avanzamos 'current' aquí, porque el bloque fusionado
            // podría unirse nuevamente con el siguiente vecino en la próxima vuelta.
        } else {
            current = current->next; // Solo avanzamos si no hubo fusión
        }
    }
}

// O(n) - Libera toda la RAM simulada al cerrar el SO
void mm_destroy(MemoryManager* mm) {
    if (mm == NULL) return;

    MemoryBlock* current = mm->head;
    while (current != NULL) {
        MemoryBlock* temp = current;
        current = current->next;
        free(temp);
    }
    free(mm);
}
