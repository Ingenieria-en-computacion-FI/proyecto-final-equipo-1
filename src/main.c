#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "memory_manager.h"

int main(int argc, char *argv[]) {
    // 1. Inicializamos nuestro "Sistema Operativo"
    // Le daremos 1024 MB de memoria RAM simulada
    MemoryManager* ram = mm_create(1024); 
    Scheduler* planificador = scheduler_create_fifo();

    int procesos_a_simular = 0;
    int modo_benchmark = 0;

    // 2. Verificamos si Python nos está mandando llamar desde benchmark.py
    if (argc > 1) {
        procesos_a_simular = atoi(argv[1]);
        modo_benchmark = 1;
        // En modo benchmark, simularemos procesos rápidos
        for (int i = 0; i < procesos_a_simular; i++) {
            scheduler_add_process(planificador, i, 10);
        }
    } else {
        // 3. Modo normal: Leemos el archivo que generó generate_process.py
        printf("Iniciando OS... Leyendo procesos.csv\n");
        FILE* archivo_entrada = fopen("data/inputs/procesos.csv", "r");
        
        if (archivo_entrada == NULL) {
            printf("Error: Primero debes correr generate_process.py en Python.\n");
            return 1;
        }

        int pid, burst, mem;
        // Leemos cada línea separada por comas (CSV)
        while (fscanf(archivo_entrada, "%d,%d,%d", &pid, &burst, &mem) == 3) {
            scheduler_add_process(planificador, pid, burst);
            procesos_a_simular++;
        }
        fclose(archivo_entrada);
    }

    // 4. Ejecutamos la simulación y guardamos resultados
    FILE* archivo_salida = NULL;
    if (!modo_benchmark) {
        archivo_salida = fopen("data/outputs/resultados.csv", "w");
        fprintf(archivo_salida, "pid,estado,direccion_memoria\n");
    }

    int pid_actual;
    int procesos_completados = 0;

    // Mientras haya procesos en la fila...
    while ((pid_actual = scheduler_next(planificador)) != -1) {
        // Intentamos darle 50MB de RAM a cada proceso
        int direccion = mm_allocate_first_fit(ram, 50); 
        
        if (direccion >= 0) {
            if (!modo_benchmark) {
                fprintf(archivo_salida, "%d,COMPLETADO,%d\n", pid_actual, direccion);
            }
            // Simulamos que terminó y liberamos su memoria para el siguiente
            mm_free(ram, pid_actual); 
            procesos_completados++;
        } else {
            if (!modo_benchmark) {
                fprintf(archivo_salida, "%d,RECHAZADO_POR_FALTA_DE_RAM,-1\n", pid_actual);
            }
        }
    }

    if (!modo_benchmark) {
        fclose(archivo_salida);
        printf("Simulacion exitosa. Se procesaron %d procesos.\n", procesos_completados);
        printf("Resultados guardados en data/outputs/resultados.csv\n");
    }

    // 5. Apagamos el sistema y liberamos estructuras
    scheduler_destroy(planificador);
    mm_destroy(ram);

    return 0;
}
