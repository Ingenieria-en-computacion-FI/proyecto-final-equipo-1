#include <stdlib.h>
#include "scheduler.h"
#include "queue.h"
#include "circular_queue.h"

struct Scheduler {
    int type; // 0 = FIFO, 1 = Round Robin, 2 = SJF
    Queue* fifo_queue;
    CircularQueue* rr_queue;
    int quantum;
    
    // Arreglos para SJF
    int sjf_pids[10000];
    int sjf_bursts[10000];
    int sjf_count;
};

Scheduler *scheduler_create_fifo() {
    Scheduler* s = malloc(sizeof(Scheduler));
    if (s) { 
        s->type = 0; 
        s->fifo_queue = queue_create(); 
        s->rr_queue = NULL; s->quantum = 0; 
        s->sjf_count = 0; 
    }
    return s;
}

Scheduler *scheduler_create_round_robin(int quantum) {
    Scheduler* s = malloc(sizeof(Scheduler));
    if (s) { 
        s->type = 1; 
        s->fifo_queue = NULL; 
        s->rr_queue = cq_create(10000); 
        s->quantum = quantum; 
        s->sjf_count = 0; 
    }
    return s;
}

Scheduler *scheduler_create_sjf() {
    Scheduler* s = malloc(sizeof(Scheduler));
    if (s) { 
        s->type = 2; 
        s->fifo_queue = NULL; 
        s->rr_queue = NULL; 
        s->quantum = 0; 
        s->sjf_count = 0; 
    }
    return s;
}

void scheduler_add_process(Scheduler *scheduler, int pid, int burst_time) {
    if (scheduler == NULL) return;

    if (scheduler->type == 0) {
        enqueue(scheduler->fifo_queue, pid);
    } else if (scheduler->type == 1) {
        cq_enqueue(scheduler->rr_queue, pid);
    } else if (scheduler->type == 2) {
        // SJF: Guardamos el proceso y su tiempo de ráfaga
        scheduler->sjf_pids[scheduler->sjf_count] = pid;
        scheduler->sjf_bursts[scheduler->sjf_count] = burst_time;
        scheduler->sjf_count++;
    }
}

int scheduler_next(Scheduler *scheduler) {
    if (scheduler == NULL) return -1;

    if (scheduler->type == 0) {
        return dequeue(scheduler->fifo_queue);
    } else if (scheduler->type == 1) {
        return cq_dequeue(scheduler->rr_queue);
    } else if (scheduler->type == 2) {
        // SJF (ALGORITMO GREEDY): Buscar el proceso que tarde menos (menor burst_time)
        if (scheduler->sjf_count == 0) return -1;
        
        int min_index = 0;
        for (int i = 1; i < scheduler->sjf_count; i++) {
            if (scheduler->sjf_bursts[i] < scheduler->sjf_bursts[min_index]) {
                min_index = i;
            }
        }
        
        int pid_elegido = scheduler->sjf_pids[min_index];
        
        // Lo sacamos de la fila reacomodando el arreglo en O(1)
        scheduler->sjf_pids[min_index] = scheduler->sjf_pids[scheduler->sjf_count - 1];
        scheduler->sjf_bursts[min_index] = scheduler->sjf_bursts[scheduler->sjf_count - 1];
        scheduler->sjf_count--;
        
        return pid_elegido;
    }
    return -1;
}

void scheduler_destroy(Scheduler *scheduler) {
    if (scheduler == NULL) return;
    if (scheduler->type == 0) queue_destroy(scheduler->fifo_queue);
    else if (scheduler->type == 1) cq_destroy(scheduler->rr_queue);
    free(scheduler);
}