#include <stdlib.h>
#include "algorithms.h"
void divide_conquer_compact(MemoryManager* mm) {
    if (mm == NULL || mm->head == NULL) return;
    MemoryBlock* current = mm->head;
    int total_occupied = 0;
    while (current != NULL) {
        if (current->free == 0) {
            total_occupied += current->size;
        }
        current = current->next;
    }
    current = mm->head->next;
    while (current != NULL) {
        MemoryBlock* temp = current;
        current = current->next;
        free(temp);
    }
    if (total_occupied > 0) {
        mm->head->size = total_occupied;
        mm->head->free = 0;
        mm->head->start = 0;
        
        if (mm->total_memory > total_occupied) {
            MemoryBlock* free_block = malloc(sizeof(MemoryBlock));
            free_block->start = total_occupied;
            free_block->size = mm->total_memory - total_occupied;
            free_block->free = 1;
            free_block->pid = -1;
            free_block->next = NULL;
            free_block->prev = mm->head;
            
            mm->head->next = free_block;
        } else {
            mm->head->next = NULL;
        }
    } else {
        mm->head->size = mm->total_memory;
        mm->head->free = 1;
        mm->head->next = NULL;
    }
}
