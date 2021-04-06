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
#define CONFIG_PATH "config/config.cfg"

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
static config_options_t config_options_create(void);

/**
 * Prints the loaded configuration
 * 
 * @function
 * @private
 * @param is_config the configuration option
 */
static void config_options_print(const config_options_t *);

// ============================================================================================================
//                               ***** Private Functions Definitions *****
// ============================================================================================================

static config_options_t config_options_create(void)
{
    //Exporting Structure config options
    config_options_t es_config;

    es_config.config = config_create(CONFIG_PATH);
    assert(es_config.config != NULL);
    return es_config;
}

static void config_options_print(const config_options_t *is_config)
{
    puts("\n========================= GLOBAL CONFIGURATION ==============================");
    printf("IP= %s\n", (const char *)config_get_ip(is_config));
    printf("PORT= %s\n", (const char *)config_get_port(is_config));
    printf("VALUE= %s\n", (const char *)config_get_value(is_config));
    puts("=============================================================================\n");
}

// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

config_options_t config_options_init(void)
{
    // Exporting Structure config, the created config options
    config_options_t es_config = config_options_create();

    // DEBUG ONLY: print loaded config
    config_options_print(&es_config);

    return es_config;
}

char *config_get_ip(const config_options_t *is_config)
{
    return config_get_string_value(is_config->config, IP_KEY);
}

char *config_get_port(const config_options_t *is_config)
{
    return config_get_string_value(is_config->config, PORT_KEY);
}

char *config_get_value(const config_options_t *is_config)
{
    return config_get_string_value(is_config->config, VALUE_KEY);
}

void config_options_finish(config_options_t *is_config)
{
    config_destroy(is_config->config);
}