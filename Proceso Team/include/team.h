#pragma once

#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <commons/collections/list.h>
#include <commons/string.h>
#include <commons/process.h>
#include "teamconfig.h"
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// Just for aesthetics
#define WORLD_POSITION world_pos
#define PRINT_TEST 0
#define LIBERAR 1

#ifndef VERBOSE
#define VERBOSE 1
#endif

/*  Position Vector of 32 bit    */
typedef struct vector2D_32b
{
	uint32_t x_;
	uint32_t y_;

} world_pos;

// ============================================================================================================
//                                            ***** TRAINERS *****
// ============================================================================================================

/*  Imported from 5 - status of process diagram  */
typedef enum thread_status{
    NEW,
    READY,
    BLOCKED,
    EXECUTING,
    EXIT
} Status;

/* Objectives come as:
 *
 * [Pikachu|Pikachu|Squirtle|Pidgey,Pikachu|Charmander|Charmander,Squirtle|Bulbasaur]
 * 
 * Where between token '|' there are pokemons and ',' trainers
 * 
 */


/* Trainers */
typedef struct trainer_list
{
    /*  Trainer's Inventory - Name and number of Pokemons in inventory  */
    t_list* bag;
    
    /*  About objective */   
    t_list* personal_objective;
    
    /*  Process Related  */
    Status actual_status;
    unsigned int thread_id;
    uint32_t trainer_id;

    /*  Position    */
    WORLD_POSITION actual_position;
} Trainer;


/* Asigna Thread Id al Trainer*/
void Trainer_dar_id(void* elemento);

// ============================================================================================================
//                                                ***** TEAM *****
// ============================================================================================================

/*  Team
 * =================
 *  config file
 *  size of team
 *  list of global objective
 *  list of trainers
 * ==================
 */
typedef struct process_team
{
    /* Global configurations */
    t_config* team_config;
        /*  Process execution realted   */
        uint32_t cpu_cycle;
        uint32_t quantum;
        uint32_t initial_estimation;
        double alpha;
        char* planning_algorithm;
        /*  Connection related  */
        uint32_t reconnection_time;
        char* broker_IP;
        char* broker_port;
    /* About Team */
    int team_size;
    t_list* global_objective;
    t_list* trainers;
} Team;

/*  Initializes the TEAM PROCESS    */
Team* Team_Init(void);

/* Creates a team */
Team* Team_create(void);

/* Loads the trainers information from File Config */
void Team_load_trainers_config( Team* team);

/* Loads global configuration (Connection and planification data) */
void Team_load_global_config(Team *this_team);

/* Admite los procesos, que pasan a la cola de Ready*/
int Team_admitir_trainers (Team* team);

/* Creates Trainers threads */
int Team_create_trainers(Team* team);

/* Frees memory */
int Team_Destroy(Team* team);

/* Frees Trianers' memory and trheads (Por ahora tambien hace el join)*/
int Team_destroy_trainers (Team* team);

/* Frees Team's list trainers and list global objective*/
void Team_destroy_trainers_and_objective(Team* team);
