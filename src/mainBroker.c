#include <connBroker.h>
#include <stdio.h>

int main(void)
{
    char msg [18];
    int server;
    int conn_in;

    db_create_server(&server, "localhost", "4010", AF_INET, AI_PASSIVE, SOCK_STREAM, 10);

    db_accept(server, &conn_in);

    db_recv(conn_in, msg, 18);
    db_send(conn_in, "Hello From Broker Server", 18);

    db_close_socket(conn_in, 2);
    db_close_socket(server, 2);

    puts(msg);

    return 0;
}