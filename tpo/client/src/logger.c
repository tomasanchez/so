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

// ============================================================================================================
//                               ***** Logger Definitions *****
// ============================================================================================================

// LOG_PATH the path of log file
#define LOG_PATH "log/tp0.log"
// APP_NAME the application name
#define APP_NAME "TP-0"

// Global Structure logger
t_log *gs_logger;

// ============================================================================================================
//                               ***** Private Functions Declarations *****
// ============================================================================================================

/**
 * Creates a logger.
 * 
 * @function
 * @private
 * @return {t_log *} a new logger pointer
 */
t_log *logger_init(void);

// ============================================================================================================
//                               ***** Private Functions Definitions *****
// ============================================================================================================

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

// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

void logger_start(void)
{
    gs_logger = logger_init();
    log_info(gs_logger, "Hello, I'm a logger.");
}

void logger_end(void)
{
    log_destroy(gs_logger);
}