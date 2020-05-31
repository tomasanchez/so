#pragma once

#include <stdlib.h>
#include <connTeam.h>
#include <assert.h>
#include <inttypes.h>
#include <commons/collections/list.h>
#include <commons/string.h>
#include "teamconfig.h"

// Just for aesthetics
#define WORLD_POSITION world_pos
#define PRINT_TEST 0
#define LIBERAR 1

/*  Position Vector of 32 bit    */
typedef struct vector2D_32b
{
	uint32_t x_;
	uint32_t y_;

} world_pos;

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
    uint32_t thread_id;

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
typedef struct process_team
{
    /* Global configurations */
    t_config* team_config;
        /*  Process execution realted   */
        uint32_t cpu_cycle;
        uint32_t quantum;
        uint32_t initial_estimation;
        /*  Connection related  */
        uint32_t reconnection_time;
        char* broker_IP;
        char* broker_port;
        char* planning_algorithm;
    /* About Team */
    uint32_t team_size;
    t_list* global_objective;
    t_list* trainers;
} Team;

/* Creates a team */
Team* Team_create(void);

/*  Initializes the TEAM PROCESS    */
Team* Team_Init(void);

/* Loads the trainers information from File Config */
void Team_load_trainers_config( Team* team);

/* Spawns Trainers */
void Team_create_trainers(Team* team);

/* Loads global objectives */
void Team_load_global_config(Team *this_team);

/* Frees memory */
void Team_Destroy(Team* team);

/* Frees Team's list trainers and list global objective*/
void Team_destroy_lists(Team* team);

char* str_objective(Team* team);