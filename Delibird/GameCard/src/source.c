#include "gamecard.h"

GameCard_t* este_gamecard;

int main (void){

     puts("\nRunning...");

    /* Debugger options*/
    if(VERBOSE){
     puts("\n>>> >> >> >> > GAME CARD - DEBUGGER CONSOLE < << << << <<<\n");
     puts(" Disable this option in gcconfig.h changing VERBOSE to 0\n");
    }

    este_gamecard = GameCard_Iniciar();

    /*
        GameCard_Conectar(este_gamecard);

        while (GameCard_esta_corriendo(este_gamecard)){

            if( ! GameCard_esta_conectado(este_gamecard))
                    GameCard_Reconectar(este_gamecard);

            if (GameCard_esta_conectado (este_gamecard))
                GameCard_Escuchar_Broker(este_gamecard);
            else
                GameCard_Escuchar_GameBoy(este_gamecard)
;            
            GameCard_Actualizar(este_gamecard);
        }    
    */

    GameCard_Destroy(este_gamecard);

    return 0;
}