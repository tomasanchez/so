#include <team.h>
#include <stdio.h>

int main(void)
{
    Team squad;

    Team_Init(&squad);


    puts("Objective: ");

    puts(str_objective(&squad));
    
    return 0;
}

/*char message[18];
    int connT;

    db_create_client(&connT, "localhost", "4010", AF_INET, AI_PASSIVE, SOCK_STREAM);

    db_send(connT, "Hello from Team Client", 18);
    db_recv(connT, message, 18);

    db_close_socket(connT, 2);

    puts(message);
    */