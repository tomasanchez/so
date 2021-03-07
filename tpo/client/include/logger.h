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
 * Creates a logger.
 * 
 * @function
 * @public
 * @return {t_log *} a new logger pointer
 */
t_log *logger_init(void);