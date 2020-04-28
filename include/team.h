#pragma once

#include <stdlib.h>
#include <connTeam.h>
#include <teamLoad.h>

// Just for aesthetics
#define WORLD_POSITION db_world_pos


/*  =============================================================   TRAINERS   =============================================================   */

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

/* Objectives:
 * =================
 * list objective
 * number of pokemons
 * ==================
 */
typedef struct{

    char* objective;
    u_int32_t total_objectives;

} Objective;

/* Trainer's Inventory 
 *  Name of Pokemons in inventory
 *  number of pokemons in inventory
 */
typedef struct{
    char* its_pokemons;
    int number_of_pokemons;
} Inventory;

/* Trainers */
typedef struct
{
    /*  About objective */
    Objective* personal;
    Inventory* bag;
    
    /* Process Related */
    Status actual_status;

    /*  Position    */
    WORLD_POSITION actual_position;

} Trainer;

/*  Creates a Trainer from a string */
trainer_error Trainer_create(char* trainer);

/* Loads Objectives from a string */
trainer_error Trainer_assign_objective(char* objective);

/*  =============================================================   TEAM   =============================================================   */

/*  Team
 * =================
 *  config file
 *  size of team
 *  global objective
 *  array of trainers
 * ==================
 */
typedef struct 
{
    /* Configuration */
    t_config* team_config;

    /* About Team*/
    unsigned int team_size;
    Objective* global;
    Trainer* team[];

} Team;


/*  Initializes & Creates a team the TEAM PROCESS    */
void Team_Init(Team* team);

/*  Closes all team related structures */
void Team_ShutDown(Team* this_team);

/* Loads File Config */
void Team_load_config( Team* team);

/*  Loads & Counts Trainers */
void Team_load_trainers(Team* team);

/* Loads global objectives */
void Team_load_global_objectives(Team* team);

/* Spawns Trainers */
void Team_create_trainers(Team* team);

/* For debugging */
char* str_objective(Team* team);