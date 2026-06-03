#include <stdlib.h>
#include "memory_manager.h"

int mm_allocate_best_fit(MemoryManager* mm, int size) {
    if (mm == NULL || mm->head == NULL) return -1;

    MemoryBlock* current = mm->head;
    MemoryBlock* best_block = NULL;
    int min_size = 9999999; 

    while (current != NULL) {
        if (current->free == 1 && current->size >= size) {
            if (current->size < min_size) {
                min_size = current->size;
                best_block = current;
            }
        }
        current = current->next;
    }

    if (best_block != NULL) {
        if (best_block->size > size) {
            MemoryBlock* new_block = malloc(sizeof(MemoryBlock));
            new_block->start = best_block->start + size;
            new_block->size = best_block->size - size;
            new_block->free = 1;
            new_block->pid = -1;
            
            new_block->next = best_block->next;
            new_block->prev = best_block;
            
            if (best_block->next != NULL) {
                best_block->next->prev = new_block;
            }
            best_block->next = new_block;
            
            best_block->size = size;
        }
        best_block->free = 0;
        best_block->pid = best_block->start;
        return best_block->start;
    }

    return -1; 
}