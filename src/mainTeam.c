#include <team.h>

int main(void)
{
    Team* squad = Team_Init ();

    /*  [DEBUG] Chequeo que se cargo todo bien  */
   // Team_print_gconfig(squad);

    Team_print_trainers(squad);

    Team_Destroy(squad);

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