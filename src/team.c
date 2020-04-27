#include <team.h>
#include <string.h>

/* Wrapping configurations */
void Team_load_config(Team* this_team){
    this_team->team_config = get_config();
}

/* Wrapping malloc */
void Team_create(Team* this_team){
    this_team = malloc (sizeof(Team));
    //puts("Team Created");
}

/* Loads from configuration files */
void Team_load_global_objectives(Team* this_team){
    this_team->global->objective = get_global_objective(this_team->team_config);
}

/*Assigning Trainers objectives*/
void Team_create_trainers(Team* this_team){
}

/* Initializing all Team components */
void Team_Init(Team* this_team){

    Team_create(this_team);
    Team_load_config(this_team);
    Team_load_global_objectives(this_team);
    Team_create_trainers(this_team);

}


char* str_objective(Team* team){
return team->global->objective;
}