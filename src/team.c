#include "teamconfig.h"
#include <string.h>

/* Wrapping configurations */
void Team_get_config(Team* this_team){
    this_team->team_config = get_config();
}

/* Wrapping malloc */
Team* Team_create(void){
    return (malloc (sizeof(Team)) ); 
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