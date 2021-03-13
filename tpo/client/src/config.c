/**
 *  config.c
 * 
 *  config handler functions.
 * 
 * @file This file describes the config methods.
 * @author Tomás A. Sánchez
 * @since 03.13.2021
 */

#include "config.h"

// ============================================================================================================
//                               ***** Config Defines *****
// ============================================================================================================

// The IP key in file
#define IP_KEY "IP"
// The PORT key in file
#define PORT_KEY "PORT"
// The VALUE key in file
#define VALUE_KEY "VALUE"
// CONFIG_PATH the config file path
#define CONFIG_PATH "config/config.ini"
// STR_SIZE a standard size for configurations strings
#define STR_SIZE 32

// ============================================================================================================
//                               ***** Private Functions Declarations *****
// ============================================================================================================

/**
 * Creates a configuration option. 
 * 
 * Allocs the configurations options.
 *
 * @function
 * @private
 * @returns es_config the allocated config optios.
 */
config_options_t config_options_create(void);

/**
 * Reads configuration file.
 * 
 * @function
 * @private
 * @param is_config the configuration option
 */
void config_options_load(config_options_t *);

/**
 * Prints the loaded configuration
 * 
 * @function
 * @private
 * @param is_config the configuration option
 */
void config_options_print(const config_options_t *);

// ============================================================================================================
//                               ***** Private Functions Definitions *****
// ============================================================================================================

config_options_t config_options_create(void)
{
    //Exporting Structure config options
    config_options_t es_config;

    es_config.config = config_create(CONFIG_PATH);
    assert(es_config.config != NULL);
    // Corresponding allocations
    es_config.ip = calloc(sizeof(char), STR_SIZE);
    es_config.port = calloc(sizeof(char), STR_SIZE);
    es_config.value = calloc(sizeof(char), STR_SIZE);

    // End of allocations.

    return es_config;
}

void config_options_load(config_options_t *is_config)
{
    // Config file read
    is_config->ip = strcpy(is_config->ip, config_get_string_value(is_config->config, IP_KEY));
    is_config->value = strcpy(is_config->value, config_get_string_value(is_config->config, VALUE_KEY));
    is_config->port = strcpy(is_config->port, config_get_string_value(is_config->config, PORT_KEY));

    // As config file is no longer needes, better to destroy it.
    config_destroy(is_config->config);
}

void config_options_print(const config_options_t *is_config)
{
    puts("\n========================= GLOBAL CONFIGURATION ==============================");
    printf("IP= %s\n", is_config->ip);
    printf("PORT= %s\n", is_config->port);
    printf("VALUE= %s\n", is_config->value);
    puts("=============================================================================");
}

// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

config_options_t config_options_init(void)
{
    // Exporting Structure config, the created config options
    config_options_t es_config = config_options_create();

    // Read config options
    config_options_load(&es_config);

    // DEBUG ONLY: print loaded config
    config_options_print(&es_config);

    return es_config;
}

void config_options_finish(config_options_t *is_config)
{
    // Corresponding de-allocations
    free(is_config->ip);
    free(is_config->port);
    free(is_config->value);
}