/**
 * config.h
 * 
 * Header file for config handler functions.
 * 
 * @file This file describes the config methods.
 * @author Tomás A. Sánchez
 * @since 03.13.2021
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <commons/config.h>

/**
 * Configuration Options. 
 * 
 * Masks configurations methods.
 * @class
 * @public
 */
typedef struct Config
{
    // t_config the configuration file
    t_config *config;

} config_options_t;

/**
 * Initializes configuration options. 
 * 
 * Creates and loads all options.
 * 
 * @function
 * @public
 * @returns es_config the loaded Configuration Options
 */
config_options_t config_options_init(void);

/**
 * Obtains strring value of Port. 
 * 
 * @function
 * @public
 * @param is_config the configuration structure
 * @returns the corresponding string value
 */
char *config_get_port(const config_options_t *);

/**
 * Obtains strring value of IP. 
 * 
 * @function
 * @public
 * @param is_config the configuration structure
 * @returns the corresponding string value
 */
char *config_get_ip(const config_options_t *);

/**
 * Obtains strring value of Key. 
 * 
 * @function
 * @public
 * @param is_config the configuration structure
 * @returns the corresponding string value
 */
char *config_get_value(const config_options_t *);

/**
 * Ends cycle of life of config options
 * 
 * Makes corresponding Frees.
 * 
 * @function
 * @public
 * @param is_config the configuration option
 */
void config_options_finish(config_options_t *);