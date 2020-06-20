#include "scheduler.h"

#define STR_SIZE 15

static Scheduler_t* OS;
extern t_list** g_Entrenadores;


/* =============================================================== Funciones Table ===============================================================   */

static int Table_get_trainer_index(unsigned int trainer_id){
    int counter = 0;
    int size = list_size(*g_Entrenadores);

    for (counter = 0; counter < size; counter++){

        if (OS->tabla[counter].index == trainer_id) break;
    }

    return counter;
}

static unsigned int Table_get_trainer_thread(int trainer_id){
    return OS->tabla[Table_get_trainer_index(trainer_id)].id;
}

/* =============================================================== Funciones Queues ===============================================================   */

// ============================================================================================================
//                               ***** First Come First Serve - FCFS  *****
// ============================================================================================================
/*  FCFS - Turnos
    mutex atado a una condicion
    turno actual se incrementa por signal
    turnos totales se incrementa por wait
*/
typedef struct Queue_fcfs{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    uint32_t current_turn, total_turns;
} fcfs_queue_t;

/* hace un lock a los threads en una "queue" en un mutex. Incrementa el total de turnos */
static void fcfs_wait(fcfs_queue_t* queue);

/* Desbloquea al siguiente thread de la cola. */
static void fcfs_signal(fcfs_queue_t* queue);

/* inicializa FIFO queue  */
static void fcfs_Qinit(fcfs_queue_t* queue);

/* libera los recursos de una FIFO queue */
static void fcfs_Qdestroy(fcfs_queue_t* queue);


/* =============================================================== SCHEDULER ===============================================================   */

/* Paso algoritmo a int para usar en switch */
static inline algorithm_t Scheduler_get_algorithm(const char* algorithm){
    
    if (strcmp("FIFO", algorithm) == 0)
        return FIFO;
    else if(strcmp("RR", algorithm) == 0)
        return RR;
    else if (strcmp("SJF-SD", algorithm) == 0)
        return SJF_SD;
    else
        return SJF_CD;
        
}

/* Creo segun el algoritmo  */
Scheduler_t* Scheduler_create(const char* algoritmo){

    //printf("[SCHEDULER] MEM: %X\n", g_Entrenadores);

    /* Mallocs que no dependen del algoritmo */
    Scheduler_t* this_scheduler = malloc(sizeof(Scheduler_t));
    this_scheduler->counter = 0;
    this_scheduler->algoritmo = Scheduler_get_algorithm(algoritmo);
    this_scheduler->tabla = calloc(sizeof(linker_t), list_size(*g_Entrenadores));
    
    if(VERBOSE)
        printf("[DEBUG] (SCHEDULER_CREATE) Se esta deberia haber creado algoritmo %s\n", algoritmo);


    /* Inicializando las colas de entrenadores (datos)*/
    this_scheduler->entrenadores_ready = queue_create();
    this_scheduler->entrenadores_aux = queue_create();


    /* Mallocs correspondientes, segun el algoritmo correspondiente */
    switch (this_scheduler->algoritmo)
    {
    case FIFO:
        /*===============================   Firts Come First Served   =========================================*/

        if(VERBOSE)
            puts("[DEBUG] (SCHEDULER_CREATE) Creando algoritmo First Come, First Served...");
        this_scheduler->ready_queue = malloc(sizeof(fcfs_queue_t));
        this_scheduler->blocked_queue = malloc(sizeof(fcfs_queue_t));
        if(VERBOSE)
            puts("[DEBUG] (SCHEDULER_CREATE) Se creo algoritmo FCFS");
        break;
    
    default: 
            puts("Algoritmo todavia no definido, Saliendo del programa...");
            exit(-1);
        break;
    }

    return this_scheduler;
}

int Scheduler_queue_init(Scheduler_t* this_scheduler){

    /* Este cola siempre se inicia, sin importar el agoritmo */
    sem_init(&(this_scheduler->new_queue), 0, 0);

    /* El mutex tambien es independiente*/
    pthread_mutex_init(&(this_scheduler->mx), NULL);

    /* Estas colas dependen de cada algoritmo*/
    switch (this_scheduler->algoritmo)
    {
    /*===============================   Firs Come Fist Served   =========================================*/
    case FIFO:
        fcfs_Qinit((fcfs_queue_t *) (this_scheduler->ready_queue));
        fcfs_Qinit((fcfs_queue_t *) (this_scheduler->blocked_queue));
        break;

    /*===============================    Roun Robin    =========================================*/
    
    /*===============================    Shortest Job Next (sin desalojo)    =========================================*/

    /*===============================    Shortest Job Next (con desalojo)    =========================================*/

    default:
        exit(-1);
        break;
    }


    return 0;
}

/* Encola a los threads en la cola Nuevos   */
static int Scheduler_enqueue_New(void){
    
    if (VERBOSE)
        printf("[DEBUG] (SCHEDULER_ENQUEUE_NEW) Thread %d llego a New_Queue \n", process_get_thread_id());

    /* La cola es un semaforo   */
    return sem_wait(&(OS->new_queue));
}

int Scheduler_admitir_procesos(void){

    /* Hago un clean de las iteraciones del contador del "sistema operativo" */
    OS->counter = 0;
    return sem_post(&(OS->new_queue));
}

/* Encolar en ready */
static int Scheduler_enqueue_Ready(void){

   switch (OS->algoritmo)
   {
   case FIFO:

        if(VERBOSE)
            printf("[DEBUG] (SCHEDULER_ENQUEUE_READY) Thread %d saliendo...\n", process_get_thread_id());
        pthread_exit(NULL);
       //fcfs_wait((fcfs_queue_t *) (OS->ready_queue));
       break;
   
   default:
        puts("No definido, saliendo...");
        exit(-1);
       break;
   }


   return 0;
}




int Scheduler_Init(const char* algoritmo, t_list* trainers){

    g_Entrenadores = &trainers;
    OS = Scheduler_create(algoritmo);
    Scheduler_queue_init(OS);

    return 0;
}


int Scheduler_Destroy(void){

    sem_destroy(&(OS->new_queue));
    pthread_mutex_destroy(&(OS->mx));
    free(OS->tabla);


    /*Destruccion de los datos de cola*/
    queue_is_empty(OS->entrenadores_ready) ? queue_destroy(OS->entrenadores_ready) : queue_destroy_and_destroy_elements(OS->entrenadores_ready, _trainer_destroy);
    queue_is_empty(OS->entrenadores_aux) ? queue_destroy (OS->entrenadores_aux): queue_destroy_and_destroy_elements(OS->entrenadores_aux, _trainer_destroy);

    /* Segun el Algoritmo:  */
    switch (OS->algoritmo)
    {
    /*===============================   Firs Come Fist Served   =========================================*/
    case FIFO:

        fcfs_Qdestroy((fcfs_queue_t*)(OS->ready_queue));
        free(OS->ready_queue);

        fcfs_Qdestroy((fcfs_queue_t*)(OS->blocked_queue));
        free(OS->blocked_queue);
        free(OS);
        break;

    /*===============================    Roun Robin    =========================================*/
    
    /*===============================    Shortest Job Next (sin desalojo)    =========================================*/

    /*===============================    Shortest Job Next (con desalojo)    =========================================*/
    
    default: free(OS);
        break;
    } 
     
    return 0;
}

/* =============================================================== Ejecucion  ===============================================================   */

void* start_execution(void* arg){
    
    arg = NULL;
    // 
    //  - Seccion Critica - Variable Global -
    pthread_mutex_lock(&(OS->mx));

    /*  Asocio trainer de la lista global con el proceso que se encargara de sus acciones */
    Trainer * entrandor_link = list_get(*g_Entrenadores, OS->counter);
    
    OS->tabla[OS->counter].id = entrandor_link->thread_id = process_get_thread_id();
    OS->tabla[OS->counter].index = OS->counter;
    
    if (VERBOSE)
        printf("[DEBUG] (SCHEDULER_START_EXECUTION) Nuevo thread %d\t con entrenador id %d\n", entrandor_link->thread_id, OS->counter);
    
    OS->counter++;
    pthread_mutex_unlock(&(OS->mx));
    // - Fin Seccion Critica - Variable Global -
    //

    Scheduler_enqueue_New();
    Scheduler_enqueue_Ready();

    return arg;
}




/* =============================================================== First Come First Served  ===============================================================   */

static void fcfs_wait(fcfs_queue_t* queue)
{
    uint32_t turn;

    /* - -  Seccion critica - -   */
    pthread_mutex_lock(&queue->mutex);
    /* Asigno el turno y aumento total de turnos    */
    turn = queue->total_turns++;

    /* Espera activa de turno */
    while (turn != queue->current_turn)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    pthread_mutex_unlock(&queue->mutex);
    /* - - Fin Seccion critica - -  */
}

static void fcfs_signal(fcfs_queue_t* queue)
{

    /* - - Seccion Critica - -  */
    pthread_mutex_lock(&queue->mutex);
    /* Paso al siguiente turno  */
    queue->current_turn++;

    pthread_cond_broadcast(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
    /* - - Fin seccion critica - - */
}

static void fcfs_Qinit (fcfs_queue_t* queue){

    /* Ambos deben arrancar en el mismo numero, preferentemente cero */
    queue->total_turns = queue->current_turn = 0;

    /* inicializacion standard y chequeo */
    pthread_cond_init(&queue->cond, NULL);
    assert(&queue->cond);
    pthread_mutex_init(&queue->mutex,NULL);
    assert(&queue->mutex);

}

static void fcfs_Qdestroy(fcfs_queue_t* queue){

    pthread_cond_destroy(&queue->cond);
    pthread_mutex_destroy(&queue->mutex);
}