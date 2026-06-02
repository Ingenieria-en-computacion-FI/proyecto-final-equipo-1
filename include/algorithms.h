#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "memory_manager.h"
#include "stack.h"
#include "process.h"

int brute_force_worst_fit(MemoryManager* mm, int size);
int backtracking_allocation(MemoryManager* mm, Stack* history, int pid, int size);
void divide_conquer_compact(MemoryManager* mm);
int binary_search_process(Process arr[], int low, int high, int target_pid);
int dp_knapsack_processes(int ram_disponible, int pesos_memoria[], int prioridades[], int n);

#endif
