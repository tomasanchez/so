#include "team.h"

#define STR_SIZE 15

/* Wrapping configurations */
void Team_get_config(Team* this_team){
    this_team->team_config = get_config();
}

/* Wrapping malloc */
Team* Team_create(void){
    Team* this_team = malloc (sizeof(Team));
    
    /* Supongo Un maximo de 15 characters para esto*/
    this_team->broker_IP = malloc(sizeof(char) * STR_SIZE);
    this_team->broker_port = malloc(sizeof(char) * STR_SIZE);
    this_team->planning_algorithm = malloc(sizeof(char) * STR_SIZE);

    return this_team;
}


/* Initializing all Team components */
Team * Team_Init(void){

    Team *this_team = Team_create();

    /*  Config load & setup */
    Team_get_config(this_team);
    Team_load_trainers_config(this_team);
    Team_load_global_config(this_team);

    /* Adjust global objective */

    return (this_team);

}

void Team_Destroy(Team* this_team){
    
    /* Destroying configuration parameters */
    Team_destroy_lists(this_team);
    Team_destroy_connections(this_team);

    free(this_team);
}