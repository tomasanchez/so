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

    if (client_start() EQ OK)
    {
        while (client_is_running())
        {
            client_read();
            client_send_message();
        }

        return client_end();
    }
    else

        return ERROR;
}
