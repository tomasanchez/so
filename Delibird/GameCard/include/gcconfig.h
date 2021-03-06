#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <inttypes.h>
#include <commons/config.h>
#include <commons/string.h>


#ifndef VERBOSE
#define VERBOSE 1
#endif

// Para estetitca
#define Tiempo_t int
#define CONFIG_PATH "config/config.ini"

/*  Estructura Contenedora de Configuraciones */
typedef struct Configurations{
    
    //El archivo en si
    t_config * config_file;

    // Tiempos
    Tiempo_t reconexion;
    Tiempo_t reintento_operacion;
    Tiempo_t retardo_operacion;

    // Conexion
    char * punto_montaje_tall_grass;
    char * ip_broker;
    uint32_t puerto_broker;

} Config_t;

/* Imprime la configuracion cargada */
void Config_puts(Config_t * config);

/* Carga a memoria los campos de configuracion  */
void Config_cargar_configs(Config_t * cf_a_cargar);

/* Almacena el espacio necesario para las configuraciones*/
Config_t * Config_Create(void);

/* Desaloja el espacio de memoria utilizado por las configuraciones*/
void Config_Destroy (Config_t * cf_a_destruir);