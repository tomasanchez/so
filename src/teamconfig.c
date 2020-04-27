#include <teamconfig.h>

/**/
t_config* get_config(){
    t_config* ret =  config_create("config/config.ini");
    ret == NULL? puts("[ERROR] CONFIG: FILE NOT OPENED") : puts("[DEBUG] Config loaded");
    return ret;
}

char* get_global_objective(t_config* configurations){
    return config_get_string_value(configurations,"OBJETIVOS_ENTRENADORES");
}