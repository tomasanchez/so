#include "gcconfig.h"

// ============================================================================================================
//                               ***** Función parar leer las configuraciones*****
// ============================================================================================================

static inline t_config* abrir_config(){
    t_config* cfile =  config_create(CONFIG_PATH);
    cfile == NULL && VERBOSE? puts("[GameCard/Init/Create/Abrir_Config] No se pudo arbir el archivo") : puts("[GameCard/Init/Create/Abrir_Config] Configuracion abierta");
    assert(cfile);
    return cfile;
}


void Config_cargar_configs(Config_t * esta_config){
    
    if(VERBOSE)
    puts("[Init/Config_cargar_configs] Cargando datos de configuaracion...");

    // Tiempos
    esta_config->reconexion             = config_get_int_value(esta_config->config_file, "TIEMPO_DE_REINTENTO_CONEXION");
    esta_config->reintento_operacion    = config_get_int_value(esta_config->config_file, "TIEMPO_DE_REINTENTO_OPERACION");
    esta_config->retardo_operacion      = config_get_int_value(esta_config->config_file, "TIEMPO_RETARDO_OPERACION");

    //Conexion
    string_append(&(esta_config->punto_montaje_tall_grass), config_get_string_value(esta_config->config_file, "PUNTO_MONTAJE_TALLGRASS"));
    string_append(&(esta_config->ip_broker), config_get_string_value(esta_config->config_file, "IP_BROKER"));
    esta_config->puerto_broker          = config_get_int_value(esta_config->config_file, "PUERTO_BROKER");

    if(VERBOSE)
    puts("[Init/Config_cargar_config] Datos cargados, liberando t_config...");
    config_destroy(esta_config->config_file);
    if(VERBOSE)
    puts("[Init/Config_cargar_configs] t_config eliminado.");
}


void Config_puts(Config_t * config){
    puts ("\n========================= CONFIGURATION ==============================");
    printf ("TIEMPO_RECONEXION= %d\n", config->reconexion);
    printf ("TIEMPO_REINTENTO_OPERACION= %d\n",config->reintento_operacion);
    printf ("TIEMPO_RETARDO_OPERACION= %d\n",config->retardo_operacion);
    printf ("PUNTO_MONTAJE_TALLGRASS= %s\n", config->punto_montaje_tall_grass);
    printf ("IP_BROKER= %s\n", config->ip_broker);
    printf ("PUERTO_BROKER= %d\n", config->puerto_broker);
    puts("=============================================================================");
}


// ============================================================================================================
//                               ***** Función parar Crear y Destruir las configuraciones*****
// ============================================================================================================
Config_t * Config_Create(){

    // Malloc correspondiente
    Config_t * nueva_conf = (Config_t * ) malloc (sizeof(Config_t));

    // Abro el archivo
    assert (NULL != (nueva_conf->config_file = abrir_config(CONFIG_PATH)));

    nueva_conf->ip_broker = string_new();
    nueva_conf->punto_montaje_tall_grass = string_new();

    return nueva_conf;
}

void Config_Destroy (Config_t * esta_config ){

    if(VERBOSE)
    puts("[GC_DESTROY/Config_Destroy] Eliminando configuraciones cargadas...");
    free(esta_config->ip_broker);
    free (esta_config->punto_montaje_tall_grass);
    free(esta_config);
    puts("[GC_DESTROY/Config_Destroy] Se libero: IP_BROKER, PTO_MONTAJE y la configuracion.");
}