/**
 * client.h
 * 
 * Header file for client importing functions.
 * 
 * @file This file describes the importing functions.
 * @author Tomás A. Sánchez
 * @since 03.07.2021
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "config.h"

// Equals
#define EQ ==
// No Error
#define OK 0
// Error
#define ERROR -1

/**
 * Initialices the Client program.
 * 
 * @function
 * @returns 0 if client started successfully
 * @public
 */
int client_start(void);

/**
 * 
 * Wheter the program continues running
 * 
 * @function
 * @returns true while no empty input string
 * @public
 */
bool client_is_running(void);

/**
 * Reads a line from console
 * 
 * @function
 * @public
 */
void client_read(void);

/**
 * Sends the read message to the server
 * 
 * @function
 * @public
 * @returns if message was sent or not
 */
int client_send_message(void);

/**
 * Finishes the Client program.
 * 
 * @function
 * @returns 0 if client ended successfully
 * @public
 */
int client_end(void);