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
    // connection the connection status
    int connection;
    // ip the IP to connect
    char *ip;
    // port the port where to listen
    char *port;
    // value the default value to be sent
    char *value;
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
 * Ends cycle of life of config options
 * 
 * Makes corresponding Frees.
 * 
 * @function
 * @public
 * @param is_config the configuration option
 */
void config_options_finish(config_options_t *);