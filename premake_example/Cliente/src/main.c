#include <conn.h>
#include <stdio.h>

int main(void)
{
    char msg [18];

    int conn = connect_to_server("localhost", "4010");

    send_data(conn, "Hello From Client", 18);
    recv_data(conn, msg, 18);
    
    close_connection(conn);

    puts(msg);

    return 0;
}