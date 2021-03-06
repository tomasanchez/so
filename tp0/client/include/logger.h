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
 * @param iv_line a line to cpy the input string
 * @returns wheter an empty string has been read
 * @public
 */
bool logger_console_log(char **);

/**
 * Logs a message;
 * @param iv_log the message to be logged
 * @param iv_level the level of logging
 * @public
 */
void logger_log(const char *, t_log_level);

/**
 * Ends cycle of logger.
 * 
 * @function
 * @public
 */
void logger_end(void);