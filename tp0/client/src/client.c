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
#include "connection.h"

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
    // running - if is runnig
    bool running;
    // message - a buffer for strings
    char **message;
    // connected - if is connected to server;
    bool connected;
} client_t;

// Client has detected no connection
#define NO_CONNECTION -2

// Global Structure Program - the client program itself.
static client_t gs_program;

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
 * Connects client to server.
 * 
 * @function
 * @private
 * @returns  if client's socket created succesfully
 */
static bool client_connect(void);

/**
 * Frees memory utilized by client
 * 
 * @function
 * @private
 * @returns 0 if success
 */
static int client_finish(void);

/**
 * Frees memory utilized by client message.
 * 
 * @function
 * @private
 * @returns 0 if message was deleted
 */
static int client_delete_message(void);

/**
 * Calls free connection function
 * 
 * @function
 * @private
 * @returns the close socket return
 */
static int client_disconnect(void);

// ============================================================================================================
//                               ***** Private Functions Definitions *****
// ============================================================================================================

static int client_init(void)
{
    // As it is not connected at start
    gs_program.connection = 0;
    // At first is runnig
    gs_program.running = true;
    gs_program.config_options = config_options_init();
    gs_program.message = malloc(sizeof(char *));
    *gs_program.message = NULL;

    return 0;
}

static bool client_connect(void)
{
    gs_program.connection = connect_to(config_get_ip(&gs_program.config_options), config_get_port(&gs_program.config_options));

    if (is_connected())
    {
        logger_log("Connected to server", LOG_LEVEL_INFO);
        send_message(config_get_value(&gs_program.config_options), gs_program.connection);
    }
    else
        logger_log("Could not connect to server", LOG_LEVEL_ERROR);

    return gs_program.connection > 0;
}

static int client_disconnect(void)
{
    return is_connected() ? disconnect(gs_program.connection) : NO_CONNECTION;
}

static int client_delete_message(void)
{
    free(*gs_program.message);
    *gs_program.message = NULL;
    return 0;
}

static int client_finish(void)
{
    config_options_finish(&gs_program.config_options);
    free(gs_program.message);
    return 0;
}
// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

int client_start(void)
{
    logger_start();
    client_init();
    client_connect();
    return 0;
}

bool client_is_running(void)
{
    return gs_program.running;
}

void client_read(void)
{
    gs_program.running = !logger_console_log(gs_program.message);
}

int client_send_message(void)
{
    // Local Variable bytes sent - the number of bytes send
    int lv_bytes_sent = 0;

    // Pattern matching - quick return
    if (!client_is_running())
        return 0;

    if (is_connected() && has_message(*gs_program.message))
        lv_bytes_sent = send_message(*gs_program.message, gs_program.connection);
    else
        logger_log("Message could not be sent, CLIENT is NOT CONNECTED", LOG_LEVEL_ERROR);

    // Forget message
    client_delete_message();

    return lv_bytes_sent > 0;
}

int client_end(void)
{
    client_disconnect();
    client_finish();
    logger_end();

    return 0;
}