#include "team.h"
#include "scheduler.h"

/* Tamanio de los char* que contendran la info del broker (puerto, ip, etc) */
#define STR_SIZE 15

pthread_t* g_trainers;
t_list** g_Entrenadores;


inline int Team_admitir_trainers (Team* this_team){
    int exit = 0;

    for (exit = 0; exit < this_team->team_size; exit++)
        Scheduler_admitir_procesos();

    return exit;
}


/* Wrapping configurations */
int Team_get_config(Team* this_team){
    this_team->team_config = get_config();
    return this_team->team_config != NULL ? 0 : -1;
}

/* Wrapping malloc */
Team* Team_create(void){

    Team* this_team = malloc (sizeof(Team));
    
    /*  Supongo Un maximo de STR_SIZE characters para esto   (Evita memory leaks)    */
    this_team->broker_IP = malloc(sizeof(char) * STR_SIZE);
    this_team->broker_port = malloc(sizeof(char) * STR_SIZE);
    this_team->planning_algorithm = malloc(sizeof(char) * STR_SIZE);

    return this_team;
}

/* Creates threads  */
int Team_create_trainers(Team* this_team){
    int no_threads;

    /* Creo una referencia global */
    g_Entrenadores= &(this_team->trainers);

    /* Inicializo los threads globales  */
    g_trainers = calloc(this_team->team_size, sizeof(pthread_t));

    /* Creo threads y les paso un Trainer de la Lista del Team*/
    for (no_threads = 0; no_threads < this_team->team_size; no_threads++){

        pthread_create(&g_trainers[no_threads], NULL, start_execution, NULL);

    }

 return no_threads;
}

/* Joins and destroys trainers  */
int Team_destroy_trainers (Team* this_team){

    for (int i = 0; i < this_team->team_size; i++){
        pthread_join(g_trainers[i], NULL);
    }


    Team_destroy_trainers_and_objective(this_team);
    
    free(g_trainers);

    return 0;
}

inline void Trainer_dar_id(void* trainer){
    Trainer* this_trainer = (Trainer *)trainer;
    this_trainer->thread_id = process_get_thread_id();
}

/* Initializing all Team components */
Team * Team_Init(void){

    Team *this_team = Team_create();

    /*  Config load & setup */
    Team_get_config(this_team);
    Team_load_trainers_config(this_team);
    Team_load_global_config(this_team);

    /* Threads Treatment */
    Scheduler_Init(this_team->planning_algorithm, this_team->trainers);
    if (Team_create_trainers(this_team) != this_team->team_size){
        printf("[ERROR]: No se crearon todos los threads. Se esperaban %d threads\n", this_team->team_size);
        exit(-1);
    }


    return (this_team);

}

int Team_Destroy(Team* this_team){
    
    Team_destroy_trainers(this_team);
    Team_destroy_connections(this_team);

    Scheduler_Destroy();

    free(this_team);

    return 0;
}