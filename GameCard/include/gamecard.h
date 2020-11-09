#pragma once

#include "gcconfig.h"


/* Estructura basica de un proceso Game Card*/
typedef struct GameCard{
    Config_t * su_configuracion;
    bool corriendo, conectado;
} GameCard_t;

/* =============================================================== Conectividad ===============================================================   */

/* Chequea si el proceso esta escuchando al Broker*/
bool GameCard_esta_conectado (GameCard_t * este_gc);



/* =============================================================== Genesis & Apocalipsis ===============================================================   */

/* Chequa si el proceso actual esta ejecutandose    */
bool GameCard_esta_corriendo (GameCard_t * este_gc);

/*  Libera la memoria utilizada */
void GameCard_Destroy(GameCard_t * este_gc);

/*Devuelve un puntero inicializado de un proceso Game Card*/
GameCard_t * GameCard_Iniciar();    