#pragma once

#include <dbconn.h>

/*  Imported from 5 - status of process diagram  */
typedef enum{
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



typedef struct 
{
    
    /* About Team*/
    Objective global;
    int team_size;
    Trainer* team[];

} Team;
