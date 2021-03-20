/**
 *  logger.h
 * 
 * Header file for logger handler functions.
 * 
 * @file This file describes the logger methods.
 * @author Tomás A. Sánchez
 * @since 03.06.2021
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <assert.h>
#include <commons/log.h>

/**
 * Starts logger.
 * 
 * @function
 * @public
 */
void logger_start(void);

/**
 * Logs an entry from console.
 * 
 * @function
 * @returns wheter an empty string has been read
 * @public
 */
bool logger_console_log(void);

/**
 * Ends cycle of logger.
 * 
 * @function
 * @public
 */
void logger_end(void);