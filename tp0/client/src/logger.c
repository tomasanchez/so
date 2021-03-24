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
#include <readline/readline.h>
#include <readline/history.h>

// ============================================================================================================
//                               ***** Logger Definitions *****
// ============================================================================================================

// LOG_PATH the path of log file
#define LOG_PATH "log/tp0.log"
// APP_NAME the application name
#define APP_NAME "TP-0"
// EMPTY STR an Empty String
#define EMPTY_STR ""

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
static t_log *logger_init(void);

// ============================================================================================================
//                               ***** Private Functions Definitions *****
// ============================================================================================================

static t_log *logger_init(void)
{
    //lv_is_active_console if console is Active
    int lv_is_active_console = true;

    //lv_log_level the lowest level of log to be logged
    t_log_level lv_log_level = LOG_LEVEL_DEBUG;

    //es_logger the logger object
    t_log *es_logger = log_create(LOG_PATH, APP_NAME, lv_is_active_console, lv_log_level);
    assert(es_logger != NULL);
    return es_logger;
}

// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

bool logger_console_log(char **ev_line)
{
    // Exporting Variable End - is end of program?
    bool ev_is_empty = false;

    // Local Variable line - the input line from console
    char *lv_line = readline(">>> ");

    ev_is_empty = strcmp(lv_line, EMPTY_STR) ? false : true;

    if (!ev_is_empty)
    {
        log_info(gs_logger, lv_line);
        // Store the line read - Remember to free it.
        *ev_line = calloc(sizeof(char), strlen(lv_line) + 1);
        strcpy(*ev_line, lv_line);
    }

    free(lv_line);

    return ev_is_empty;
}

void logger_start(void)
{
    gs_logger = logger_init();
    log_debug(gs_logger, "Initialiazing Program...");
}

void logger_end(void)
{
    log_debug(gs_logger, "Ending: success");
    rl_clear_history();
    clear_history();
    log_destroy(gs_logger);
}