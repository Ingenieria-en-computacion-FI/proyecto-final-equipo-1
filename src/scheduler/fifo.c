#include <stdlib.h>
#include "scheduler.h"
#include "queue.h"
#include "circular_queue.h"

// 1. Definimos la estructura maestra del Planificador
struct Scheduler {
    int type; // 0 = FIFO, 1 = Round Robin
    Queue* fifo_queue;
    CircularQueue* rr_queue;
    int quantum;
};

// 2. Creador para FIFO (Usa la Cola normal)
Scheduler *scheduler_create_fifo() {
    Scheduler* s = malloc(sizeof(Scheduler));
    if (s == NULL) return NULL;
    
    s->type = 0; // Marcamos que es tipo FIFO
    s->fifo_queue = queue_create();
    s->rr_queue = NULL;
    s->quantum = 0;
    
    return s;
}

// 3. Creador para Round Robin (Usa la Cola Circular)
Scheduler *scheduler_create_round_robin(int quantum) {
    Scheduler* s = malloc(sizeof(Scheduler));
    if (s == NULL) return NULL;
    
    s->type = 1; // Marcamos que es tipo Round Robin
    s->fifo_queue = NULL;
    s->rr_queue = cq_create(100); // Capacidad máxima de 100 procesos simulados
    s->quantum = quantum;
    
    return s;
}

// 4. Agregar un proceso a la fila
void scheduler_add_process(Scheduler *scheduler, int pid, int burst_time) {
    if (scheduler == NULL) return;

    // (Nota: burst_time lo usaremos en la simulación final, por ahora solo encolamos el PID)
    if (scheduler->type == 0) {
        enqueue(scheduler->fifo_queue, pid); // Si es FIFO, entra a la cola normal
    } else {
        cq_enqueue(scheduler->rr_queue, pid); // Si es RR, entra a la cola circular
    }
}

// 5. Obtener el siguiente proceso a ejecutar
int scheduler_next(Scheduler *scheduler) {
    if (scheduler == NULL) return -1;

    if (scheduler->type == 0) {
        return dequeue(scheduler->fifo_queue); // Saca de la cola normal
    } else {
        return cq_dequeue(scheduler->rr_queue); // Saca de la circular
    }
}

// 6. Destruir y liberar memoria
void scheduler_destroy(Scheduler *scheduler) {
    if (scheduler == NULL) return;

    if (scheduler->type == 0) {
        queue_destroy(scheduler->fifo_queue);
    } else {
        cq_destroy(scheduler->rr_queue);
    }
    
    free(scheduler); // Finalmente liberamos el struct Scheduler
}
