#pragma once

#include <commons/config.h>
#include <stdlib.h>
#include <stdio.h>
#include <team.h>

/*By default loads config.ini*/
t_config* get_config();

/* Libera string split */
void  free_split (char **string);

/* Frees a char pointer */
void _borrar_string (void *string);

// ============================================================================================================
//                               ***** Funciones parar imprimir listas [DEBUG] *****
// ============================================================================================================


/* Prints List de Trainer*/
void _print_Trainer_list (void *elemento);

/* Prints List of Objectives    */
void _print_Objective (void *elemento);

/* Prints list of Trainers' inventory   */
void _print_Pokemon_caugth (void *elemento);


// ============================================================================================================
//                               ***** Config Destroys *****
// ============================================================================================================ 

/* Frees a Trainer's memory */
void _trainer_destroy (void* trainer);

/* Frees, broker IP, broker port and planning algorithm*/
void Team_destroy_connections(void* Team);



