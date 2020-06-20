#pragma once

#include "team.h"
#include <commons/collections/queue.h>

/* =============================================================== Planificador ===============================================================   */

/* En el caso de los switch es mejor trabajar con enteros*/
typedef enum algorithm{
    FIFO,
    RR,
    SJF_SD,
    SJF_CD
} algorithm_t;


/* Tabla de linkeos entre entrenadores y procesos */
typedef struct asociacion{
    unsigned int index;
    unsigned int id;
} linker_t;


/*  Planificador del sistema operativo,
*   posee "queues" segun los estados de entrenador/proceso:
*   NEW - READY - BLOCKED y Algoritmo de planificacion
*/
typedef struct Scheduler{

    /* Colas, son construcicciones con"semaforos/mutex", uso void en ready y blocked para luego castear segun corresponda el algoritmo*/
    sem_t new_queue;
    void* ready_queue;
    void* blocked_queue;

    /*Datos de entrenadores, para administar (Argumentos de los pthreads)*/
    t_queue* entrenadores_ready;
    t_queue* entrenadores_aux;

    unsigned int counter;
    linker_t* tabla;
    pthread_mutex_t mx;
    algorithm_t algoritmo;

} Scheduler_t;

/* Resetea el contador interno del Scheduler */
int Scheduler_reset_counter();

/* Comienza a ejecutar thread   */
void* start_execution(void* arg);

/* Genera un pointer a un scheduler, y crea las colas segun el algoritmo*/
Scheduler_t* Scheduler_create(const char* algoritmo);

/* Inicializa todas las queues  */
int Scheduler_queue_init(Scheduler_t* this_scheduler);

/* Iniciliza el Scheduler   */
int Scheduler_Init(const char* algoritmo, t_list* trainers);

/* Destroye un scheduler */
int Scheduler_Destroy(void);

/*Libera los procesos de New*/
int Scheduler_admitir_procesos(void);

