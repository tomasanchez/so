#pragma once

#include <commons/config.h>
#include <stdlib.h>
#include <stdio.h>
#include <team.h>

/*By default loads config.ini*/
t_config* get_config();
void  free_split (char **string);
void _imprimir_lista (void *elemento);
void _imprimir_objetivos (void *elemento);
void _imprimir_inventario (void *elemento);
void _imprimir_lista (void *elemento);
void _free_sub_list (void* elemento);
void _borrar_string (void *string);

