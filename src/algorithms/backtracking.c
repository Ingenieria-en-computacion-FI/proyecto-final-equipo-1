#include <stdlib.h>
#include "algorithms.h"
int backtracking_allocation(MemoryManager* mm, Stack* history, int pid, int size) {
    stack_push(history, pid);
    int address = brute_force_worst_fit(mm, size);
    if (address == -1) { 
        stack_pop(history);
        return -1;
    }
    return address;
}
