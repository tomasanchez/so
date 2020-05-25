#include <conn.h>
#include <stdio.h>

int main(void)
{
    char msg [18];

    int server = create_server("localhost", "4010");
    int conn_in = accept_conn(server);

    recv_data(conn_in, msg, 18);
    send_data(conn_in, "Hello From Server", 18);

    close_connection(conn_in);
    close_connection(server);

    puts(msg);

    return 0;
}