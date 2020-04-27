#pragma once

#include <stdlib.h>
#include <connTeam.h>
#include <commons/config.h>

// Just for aesthetics
#define WORLD_POSITION db_world_pos

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
typedef struct{

    char* objective;
    u_int32_t total_objectives;

} Objective;

/* Trainers */
typedef struct
{
    /*  About objective */
    Objective* personal;
    int pokemons_in_hand;
    
    /* Process Related */
    Status actual_status;

    /*  Position    */
    WORLD_POSITION actual_position;

} Trainer;

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
    Objective global;
    int team_size;
    Trainer* team[];

} Team;

/*  Creates a Trainer from a string */
trainer_error Trainer_create(char* trainer);

/* Loads Objectives from a string */
trainer_error Objective_load(char* objective);

/* Creates a team */
void Team_create(Team* team);

/*  Initializes the TEAM PROCESS    */
Team* Team_Init();

/* Loads File Config */
void Team_load_config(Team* team);

/* Spawns Trainers */
void Team_create_trainers(Team* team);
