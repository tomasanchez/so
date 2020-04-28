#include <team.h>
#include <string.h>

/*  =============================================================   LOAD   =============================================================   */

/* Wrapping configurations */
void Team_load_config(Team* this_team){
    this_team->team_config = get_config();
}

/* Loads from configuration files */
void Team_load_global_objectives(Team* this_team){

    /*  Objective may came between []   */
    this_team->global->objective = get_global_objective(this_team->team_config);

    /* Eliminates [] if there are any */
    this_team->global->objective = Objective_adjust(this_team->global->objective);
}



/*  =============================================================   TRAINERS   =============================================================   */

/*  Getting traines info from configuration     
void Team_load_trainers(Team* this_team){

    this_team->team_size=get_sizeof_trainers(this_team->global->objective);


}*/

/*Assigning Trainers objectives*/
void Team_create_trainers(Team* this_team){


}


/*  =============================================================   TEAM   =============================================================   */

/* Initializing all Team components */
void Team_Init(Team* this_team){

    /* Load phase */
    Team_load_config(this_team);
    Team_load_global_objectives(this_team);
    //Team_load_trainers(this_team);

    /* Assignation phase */
    Team_create_trainers(this_team);

}

/*  =============================================================   DEBUG   =============================================================   */

char* str_objective(Team* team){
return team->global->objective;
}