#include <team.h>
#include <string.h>

void liberar_listas(Team *this_team);

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

    Team_get_config(this_team);
    Team_load_trainers_config(this_team);
    Team_load_global_config(this_team);

    /* Just to test the correct liberation of the lists */

    return (this_team);

}

void Team_Destroy(Team* this_team){
    
    liberar_listas(this_team);

}