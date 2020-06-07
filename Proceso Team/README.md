# PROCESO TEAM

## Funciones

### Que es un Team?

Un team es la estructura con la que nos referiremos al conjuto de datos que requiere el proceso. Esto se puede dividir en 2 partes, una relacionada a la configuracion global, y otra con el Team en el contexto de Pokemones.

```c
typedef struct process_team
{
    /* Configuracion global */
    t_config* team_config;

        /* Sobre el proceso en si (Tenido en cuenta para la Planificacion)   */
        uint32_t cpu_cycle;
        uint32_t quantum;
        uint32_t initial_estimation;
        /* Datos de conexion */

        uint32_t reconnection_time;
        char* broker_IP;
        char* broker_port;
        char* planning_algorithm;

    /* El "Team" en el contexto de pokemones */
    uint32_t team_size;
    t_list* global_objective;
    t_list* trainers;
} Team;
```

Como se observa, tambien es posible subdivir la configuracion del proceso en tambien 2 partes, una de conexion y otra de planificacion.
Para evitar mayores complicaciones se decidio encapsularlo dentro de una unica estructura *Team*, bien podria ser:

```c
typedef struct proceso_team{

configuracion global;

t_list* entrenadores;
t_list* objetivos_totales;

} Team;
```

### Genesis y Apocalipsis de un Team

Desde el main llamamos *Team_Init()* que se encaraga de cargar configuraciones, y crear entrenadores.  Como esto se hace en el *heap*, debemos liberar los recursos utilizados con *Team_Destroy()*.

```c
Team_Init();
Team_Destroy();
```

*Team_Init()* llama a su vez a:

- *Team_create()*, Se encarga de pedir recursos (malloc)
- *Team_get_config(team)*, que obtiene el archivo de configuracion
- *Team_load_trainers_config(team)*, lee los campos de objetivos y atrapados del archivo config.
- *Team_load_global_config(team)*, lee los campos de planificacion y conexion de la configuracion, cierra el archivo config, pues ya no es necesario.

*Team_Destroy()* llama a:

- *Team_destroy_trainers_and_objective(team)*, elimina las listas entrenadores y objectivos.
- *Team_destroy_connection(team)*, libera los datos de conexion (*char pointers*).
