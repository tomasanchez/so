/**
 * client.c
 * 
 * Client implementation
 * 
 * @file This file describes the importing functions.
 * @author Tomás A. Sánchez
 * @since 03.20.2021
 */

#include "client.h"

// ============================================================================================================
//                               ***** Logger Definitions *****
// ============================================================================================================

/**
 * The Client mask.
 * 
 * @private
 * @class
 */
typedef struct Client
{
    // config_options - the configuration variables
    config_options_t config_options;
    // connection - the connection status
    int connection;

} client_t;

// Global Structure Program - the client program itself.
client_t gs_program;

// ============================================================================================================
//                               ***** Private Functions Declarations *****
// ============================================================================================================
/**
 * Initializes the client structure.
 * 
 * @function
 * @private
 * @returns 0 if client initialized succesfully
 */
static int client_init(void);

/**
 * Frees memory utilized by client
 * 
 * @function
 * @private
 * @returns 0 if success
 */
static int client_finish(void);

// ============================================================================================================
//                               ***** Private Functions Definitions *****
// ============================================================================================================
static int client_init(void)
{
    // As it is not connected at start
    gs_program.connection = 0;
    gs_program.config_options = config_options_init();

    return 0;
}

static int client_finish(void)
{
    config_options_finish(&gs_program.config_options);
    return 0;
}
// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

int client_start()
{
    logger_start();
    client_init();

    return 0;
}

int client_end()
{
    client_finish();
    logger_end();

    return 0;
}