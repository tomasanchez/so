#include <teamconfig.h>

/**/
t_config* get_config(){
return config_create("/config/config.ini");
}

char* get_global_objective(t_config* configurations){
    return config_get_string_value(configurations,"OBJETIVOS_ENTRENADORES");
}