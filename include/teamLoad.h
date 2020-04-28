#pragma once

#include<string.h>
#include <commons/string.h>
#include <commons/config.h>
#include <stdlib.h>
#include <stdio.h>

/*  =============================================================   Config   =============================================================   */


/*  By default loads config.ini */
t_config* get_config();



/*  =============================================================   Objective   =============================================================   */


/*  Loads global objective from configuration file*/
char* get_global_objective(t_config* configurations);

/*  Eliminates brackets   */
char* Objective_adjust(char* objective);

/*  =============================================================   TRAINERS   =============================================================   */
