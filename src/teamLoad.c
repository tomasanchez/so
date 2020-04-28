#include <teamLoad.h>

/*  =============================================================   CONFIG   =============================================================   */

t_config* get_config(){
    t_config* ret =  config_create("config/config.ini");
    ret == NULL? puts("[ERROR] CONFIG: FILE NOT OPENED") : puts("[DEBUG] Config loaded");
    return ret;
}


/*  =============================================================   OBJECTIVES   =============================================================   */

/*  Loads Objectives to memory*/
char* get_global_objective(t_config* configurations){
    return config_get_string_value(configurations,"OBJETIVOS_ENTRENADORES");
}

/*  Eliminates Brackets []  */
char* Objective_adjust(char* this_objective){

    int len = strlen(this_objective);
    int rbracket_adjustment,lbracket_adjustment;

        /*It is possible that objective came as "[objective1|objective2]*/

        if(string_starts_with(this_objective,"[") && string_ends_with(this_objective, "]")){
        rbracket_adjustment = 1;
        lbracket_adjustment = 2;
        }
        else{
        rbracket_adjustment = 0,
        lbracket_adjustment = 0;
        }

    return string_substring(this_objective, rbracket_adjustment, len - lbracket_adjustment);;
}

/*  =============================================================   TRAINERS   =============================================================   */

