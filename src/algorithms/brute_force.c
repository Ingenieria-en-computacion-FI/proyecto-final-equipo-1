#include <stdlib.h>
#include "algorithms.h"

int brute_force_worst_fit(MemoryManager* mm, int size) {
    if (mm == NULL || mm->head == NULL) return -1;
    MemoryBlock* current = mm->head;
    MemoryBlock* worst_block = NULL;
    int max_size = -1;
    while (current != NULL) {
        if (current->free == 1 && current->size >= size) {
            if (current->size > max_size) {
                max_size = current->size;
                worst_block = current;
            }
        }
        current = current->next;
    }

    if (worst_block != NULL) {
        worst_block->free = 0;
        worst_block->pid = worst_block->start; 
        return worst_block->start;
    }
    return -1; 
}
