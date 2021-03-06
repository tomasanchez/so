#include "gamecard.h"




/* =============================================================== Conectividad ===============================================================   */


bool GameCard_esta_conectado (GameCard_t * este_gc){
    return este_gc->conectado;
}







/* =============================================================== Genesis & Apocalipsis ===============================================================   */

bool GameCard_esta_corriendo (GameCard_t * este_gc){
    return este_gc->corriendo;
}


static GameCard_t * GameCard_Create(){
    
    // Correspondiente Malloc
    GameCard_t * nuevo_gc = (GameCard_t * ) malloc (sizeof(GameCard_t));

    // Creo su configuracion

    assert(NULL != (nuevo_gc->su_configuracion = Config_Create()));

    nuevo_gc->corriendo =  true;
    nuevo_gc->conectado = false;

    return nuevo_gc;
}

GameCard_t * GameCard_Iniciar(){

    GameCard_t * este_gamecard;

    if(VERBOSE)
    puts("[GameCard_Init] Iniciando Game Card...");
    assert (NULL != (este_gamecard = GameCard_Create()));
    if(VERBOSE)
    puts("[GameCard_Init] Game Card creado, cargando configuracion...");
    Config_cargar_configs(este_gamecard->su_configuracion);
    if(VERBOSE){
        puts("[GameCard_Init] Se cargo la siguiente configuracion...");
        Config_puts(este_gamecard->su_configuracion);
    }

    return este_gamecard;

}

void GameCard_Destroy(GameCard_t * este_gc){

    if(VERBOSE)
    puts("[GameCard_Destroy] Cerrando proceso...");
    Config_Destroy(este_gc->su_configuracion);
    free(este_gc);
    puts("[GameCard_Destroy] Se cerro el proceso con exito.");

}