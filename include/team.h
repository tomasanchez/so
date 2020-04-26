#pragma once

#include <connTeam.h>

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
    Objective personal;
    int pokemons_in_hand;
    
    /* Process Related */
    Status actual_status;

    /*  Position    */
    u_int32_t x_position;
    u_int32_t y_position;

} Trainer;

/* TEAM */
typedef struct 
{
    
    /* About Team*/
    Objective global;
    int team_size;
    Trainer* team[];

} Team;

trainer_error Trainer_Create(Team* trainer);