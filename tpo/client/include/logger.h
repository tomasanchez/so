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
 * Ends cycle of logger.
 * 
 * @function
 * @public
 */
void logger_end(void);