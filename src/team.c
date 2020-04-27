#include <team.h>
#include <string.h>

/* Wrapping configurations */
void Team_load_config(Team* this_team){

    puts("Trying to create");
    this_team->team_config = malloc(sizeof(t_config));
    puts("Mallocked");
    this_team->team_config = get_config();
}

/* Wrapping malloc */
void Team_create(Team* this_team){
    puts("Creating...");
    this_team = malloc (sizeof(Team));
}

/* Loads from configuration files */
void Team_load_global_objectives(Team* this_team){
    this_team->global = malloc (sizeof(Objective));
    char* aux = get_global_objective(this_team->team_config);
    this_team->global->objective = malloc(strlen(aux)+1);
    this_team->global->objective = aux;
}

/*Assigning Trainers objectives*/
void Team_create_trainers(Team* this_team){
}

/* Initializing all Team components */
Team* Team_Init(){

    Team* this_team;

    Team_create(this_team);
    Team_load_config(this_team);
    Team_load_global_objectives(this_team);
    Team_create_trainers(this_team);

return this_team;
}


char* str_objective(Team* team){
return team->global->objective;
}