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
    logger_start();
    config_options_t ls_config = config_options_init();
    config_options_finish(&ls_config);
    logger_end();
    return 0;
}
