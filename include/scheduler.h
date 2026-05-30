#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct Scheduler Scheduler;

// Esta es la creacion de schedulers

//FIFO

Scheduler *scheduler_create_fifo();

//Round Robin 

Scheduler *scheduler_create_round_robin(int quantum);

//Administracion de procesos

void scheduler_add_process(Scheduler *scheduler, int pid, int burst_time);

//Para obtener el siguiente procesos a ejecutar

int scheduler_next(Scheduler *scheduler);

//Liberar memoria 

void scheduler_destroy(Scheduler *scheduler);


#endif