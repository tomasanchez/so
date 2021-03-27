/**
 * main.c
 *
 * Encapsulates all functions.
 *
 * @file This files describes the client main file.
 * @author Tomás A. Sánchez
 * @since 03.06.2021
 */

#include "client.h"

int main(void)
{
    client_start();

    while (client_is_running())
    {
        client_read();
        client_send_message();
    }

    client_end();
    return 0;
}
