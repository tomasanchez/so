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

// LOG_PATH the path of log file
#define LOG_PATH "log/tp0.log"
// APP_NAME the application name
#define APP_NAME "TP-0"

t_log *logger_init(void)
{
    //lv_is_active_console if console is Active
    int lv_is_active_console = true;

    //lv_log_level the lowest level of log to be logged
    t_log_level lv_log_level = LOG_LEVEL_INFO;

    //es_logger the logger object
    t_log *es_logger = log_create(LOG_PATH, APP_NAME, lv_is_active_console, lv_log_level);
    assert(es_logger != NULL);
    return es_logger;
}