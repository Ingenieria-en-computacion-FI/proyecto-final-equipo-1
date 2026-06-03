#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include "memory_manager.h"
#include "process.h"
#include "linked_list.h"
#include "algorithms.h"

int main(int argc, char *argv[]) {
    // 1. Inicialización (ROUND ROBIN con Quantum = 2)
    MemoryManager* ram = mm_create(1024); 
    Scheduler* planificador = scheduler_create_round_robin(2); 
    LinkedList* terminados = ll_create();
    Process* tabla_procesos = malloc(sizeof(Process) * 10000);
    
    int memoria_asignada[10000] = {0}; 
    int direccion_asignada[10000] = {0}; // ¡LA SOLUCIÓN AL CONGELAMIENTO!

    int procesos_a_simular = 0;
    int modo_benchmark = (argc > 1);

    if (modo_benchmark) {
        procesos_a_simular = atoi(argv[1]);
        for (int i = 0; i < procesos_a_simular; i++) {
            tabla_procesos[i].pid = i;
            tabla_procesos[i].burst_time = 10;
            tabla_procesos[i].remaining_time = 10;
            tabla_procesos[i].memory_required = 50;
            tabla_procesos[i].state = READY; 
            scheduler_add_process(planificador, i, 10);
        }
    } else {
        FILE* archivo = fopen("data/inputs/procesos.csv", "r");
        if (archivo == NULL) return 1;

        int pid, burst, mem;
        while (fscanf(archivo, "%d,%d,%d", &pid, &burst, &mem) == 3) {
            tabla_procesos[pid].pid = pid;
            tabla_procesos[pid].burst_time = burst;
            tabla_procesos[pid].remaining_time = burst; 
            tabla_procesos[pid].memory_required = mem;
            tabla_procesos[pid].state = READY; 
            
            scheduler_add_process(planificador, pid, burst);
            procesos_a_simular++;
        }
        fclose(archivo);
    }

    int pid_actual;
    int procesos_completados = 0;
    int quantum = 2;

    // 3. Ciclo de Ejecución 
    while ((pid_actual = scheduler_next(planificador)) != -1) {
        
        if (memoria_asignada[pid_actual] == 0) {
            int direccion = mm_allocate_best_fit(ram, tabla_procesos[pid_actual].memory_required);
            
            if (direccion == -1) {
                tabla_procesos[pid_actual].state = BLOCKED;
                scheduler_add_process(planificador, pid_actual, tabla_procesos[pid_actual].remaining_time);
                continue; 
            }
            memoria_asignada[pid_actual] = 1; 
            // GUARDAMOS LA DIRECCIÓN DE MEMORIA
            direccion_asignada[pid_actual] = direccion; 
        }

        tabla_procesos[pid_actual].state = RUNNING; 
        
        int tiempo_ejecucion = (tabla_procesos[pid_actual].remaining_time < quantum) ? tabla_procesos[pid_actual].remaining_time : quantum;
        tabla_procesos[pid_actual].remaining_time -= tiempo_ejecucion;

        if (tabla_procesos[pid_actual].remaining_time > 0) {
            tabla_procesos[pid_actual].state = READY;
            scheduler_add_process(planificador, pid_actual, tabla_procesos[pid_actual].remaining_time);
        } else {
            tabla_procesos[pid_actual].state = FINISHED;
            // ¡LIBERAMOS USANDO LA DIRECCIÓN CORRECTA!
            mm_free(ram, direccion_asignada[pid_actual]); 
            ll_insert_last(terminados, pid_actual);
            procesos_completados++;
        }
    }

    if (!modo_benchmark) {
        printf("\n========================================\n");
        printf("Simulacion OS - Ejecucion Finalizada\n");
        printf("========================================\n");
        printf("Planificador: Round Robin (Quantum = 2)\n");
        printf("Manejo RAM  : Best Fit (Greedy) con Coalescencia\n");
        printf("Procesos    : %d completados exitosamente.\n", procesos_completados);
        
        printf("\n--- Evaluacion de Algoritmos Extra ---\n");
        int indice = binary_search_process(tabla_procesos, 0, procesos_a_simular - 1, 3);
        if(indice != -1) printf("[Divide y Venceras] Busqueda Binaria PID 3: Encontrado en O(log n).\n");
        
        int pesos[] = {10, 20, 30};
        int prioridades[] = {60, 100, 120};
        int max_val = dp_knapsack_processes(50, pesos, prioridades, 3);
        printf("[Programacion Dinamica] Maximizacion Knapsack (RAM 50MB): Valor optimo %d.\n", max_val);
        printf("========================================\n\n");
    }

    scheduler_destroy(planificador);
    mm_destroy(ram);
    ll_destroy(terminados);
    free(tabla_procesos);

    return 0;
}