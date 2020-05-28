#pragma once

#include <commons/config.h>
#include <stdlib.h>
#include <stdio.h>
#include <team.h>

/*By default loads config.ini*/
t_config* get_config();

/* Libera string split */
void  free_split (char **string);

/* Debug - Print */

/* Prints List de Trainer*/
void _imprimir_lista (void *elemento);

/* Prints List of Objectives    */
void _imprimir_objetivos (void *elemento);

/* Prints list of Trainers' inventory   */
void _imprimir_inventario (void *elemento);

void _free_sub_list (void* elemento);
void _borrar_string (void *string);

