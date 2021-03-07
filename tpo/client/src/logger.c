/**
 *  logger.c
 * 
 *  Logger handler functions.
 * 
 * @file This file describes the logger methods.
 * @author Tomás A. Sánchez
 * @since 03.06.2021
 */

#include "logger.h"

t_log *logger_init(void)
{
    // lv_path the file path
    char *lv_path = "log/tp0.log",
         // lv_app_name the application name
        *lv_app_name = "TP-0";

    //lv_is_active_console if console is Active
    int lv_is_active_console = true;

    //lv_log_level the lowest level of log to be logged
    t_log_level lv_log_level = LOG_LEVEL_INFO;

    //es_logger the logger object
    t_log *es_logger = log_create(lv_path, lv_app_name, lv_is_active_console, lv_log_level);
    assert(es_logger != NULL);
    return es_logger;
}