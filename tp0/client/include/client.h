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

/**
 * 
 * Initialices the Client program.
 * 
 * @function
 * @returns 0 if client started successfully
 * @public
 */
int client_start(void);

/**
 * 
 * Finishes the Client program.
 * 
 * @function
 * @returns 0 if client ended successfully
 * @public
 */
int client_end(void);