#include <team.h>

/* Un solo Team por Proceso */
static Team* squad;

int main(void)
{
    puts("\nRunning...");

    /* Debugger options*/
    if(VERBOSE){
     puts("\n>>> >> >> >> > TEAM - DEBUGGER CONSOLE < << << << <<<\n");
     puts(" Disable this option in team.h changing VERBOSE to 0\n");
    }

    squad = Team_Init ();
    
    /* DEBUG prints -> Activar en team.h VERBOSE*/
    if(VERBOSE){ 
        Team_print_gconfig(squad);
        Team_print_trainers(squad);
    }

    Team_admitir_trainers(squad);

    Team_Destroy(squad);

    puts("Exiting...\n");
    return 0;
}

/*  char message[18];
    int connT;

    db_create_client(&connT, "localhost", "4010", AF_INET, AI_PASSIVE, SOCK_STREAM);

    db_send(connT, "Hello from Team Client", 18);
    db_recv(connT, message, 18);

    db_close_socket(connT, 2);

    puts(message);
    */