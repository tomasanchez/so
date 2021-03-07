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
    t_log *ls_logger = logger_init();
    log_info(ls_logger, "Hello my love");
    log_destroy(ls_logger);

    return 0;
}
