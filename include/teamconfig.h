#pragma once

#include <commons/config.h>
#include <stdlib.h>
#include <stdio.h>

/*By default loads config.ini*/
t_config* get_config();

/*Gets global objective from configuration file*/
char* get_global_objective(t_config* configurations);