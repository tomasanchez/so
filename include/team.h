#pragma once

#include <stdlib.h>
#include <connTeam.h>
#include <teamconfig.h>
#include <commons/collections/list.h>
#include <commons/string.h>


// Just for aesthetics
#define WORLD_POSITION db_world_pos
#define PRINT_TEST 1
#define LIBERAR 1

/*  Imported from 5 - status of process diagram  */
typedef enum{
    NEW,
    READY,
    BLOCKED,
    EXECUTING,
    EXIT
} Status;

/* Error list for debugging */
typedef enum{
    TRAINER_CREATED,
    TRAINER_CREATION_FAILED,
    TRAINER_DELETED,
    TRAINER_DELETION_FAILED,
    TRAINER_OBJECTIVES,
    TRAINER_NO_OBJECTIVES
} trainer_error;


/* Objectives come as:
 *
 * [Pikachu|Pikachu|Squirtle|Pidgey,Pikachu|Charmander|Charmander,Squirtle|Bulbasaur]
 * 
 * Where between token '|' there are pokemons and ',' trainers
 * 
 */


/* Trainers */
typedef struct
{
    /*  Trainer's Inventory - Name and number of Pokemons in inventory  */
    t_list *bag;
    
    /*  About objective */   
    t_list *personal_objective;
    
    /*  Process Related  */
    Status actual_status;

    /*  Position    */
    WORLD_POSITION actual_position;
} Trainer;



/*  Team
 * =================
 *  config file
 *  size of team
 *  list of global objective
 *  list of trainers
 * ==================
 */
typedef struct 
{
    /* Global configurations */
    t_config* team_config;
        /*  Process execution realted   */
        u_int32_t cpu_cycle;
        u_int32_t quantum;
        u_int32_t initial_estimation;
        /*  Connection related  */
        u_int32_t reconnection_time;
        char* broker_IP;
        char* broker_port;
        char* planning_algorithm;
    /* About Team */
    u_int32_t team_size;
    t_list *global_objective;
    t_list *trainers;
} Team;

/*  Creates a Trainer from a string */
trainer_error Trainer_create(char* trainer);

/* Loads Objectives from a string */
trainer_error Objective_load(char* objective);

/* Creates a team */
Team * Team_create(void);

/*  Initializes the TEAM PROCESS    */
Team * Team_Init(void);

/* Loads the trainers information from File Config */
void Team_load_trainers_config( Team* team);

/* Spawns Trainers */
void Team_create_trainers(Team* team);

/* Loads global objectives */
void Team_load_global_config(Team *this_team);

/* Frees memory */
void Team_Destroy(Team* team);

char* str_objective(Team* team);