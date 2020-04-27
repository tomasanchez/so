#include <team.h>

/* Wrapping configurations */
void Team_load_config(Team* this_team){
    this_team->team_config = config_create("/config/config.ini");
}

/* Wrapping malloc */
void Team_create(Team* this_team){
    this_team = malloc (sizeof(Team));
}


void Team_create_trainers(Team* this_team){

}

Team* Team_Init(){

    Team* this_team;

    Team_create(this_team);
    Team_load_config(this_team);
    Team_create_trainers(this_team);

return this_team;
}