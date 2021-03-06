#include <teamconfig.h>
#include <assert.h>

#define CONFIG_PATH "config/config.ini"

// ============================================================================================================
//                               ***** Función parar leer las configuraciones*****
// ============================================================================================================

t_config *get_config()
{
    t_config *cfile = config_create(CONFIG_PATH);
    //cfile == NULL? puts("[ERROR] CONFIG: FILE NOT OPENED") : puts("[DEBUG] Config loaded");
    assert(cfile);
    return cfile;
}

// ============================================================================================================
//                               ***** Función parar inicializar a los entrenadores *****
// ============================================================================================================

void Team_load_trainers_config(Team *this_team)
{

    /*  Just for aesthetics */
    t_config *config = this_team->team_config;

    /*  Devuelve un array de strings, donde cada posición del array es del tipo posX|posY */
    char **pos_trainers_to_array = config_get_array_value(config, "POSICIONES_ENTRENADORES");

    /*  Devuelven un array de strings, donde cada posición del array es del tipo pok1|pok2|pok3...pokN*/
    char **pok_in_bag_to_array = config_get_array_value(config, "POKEMON_ENTRENADORES");
    char **trainers_obj_to_array = config_get_array_value(config, "OBJETIVOS_ENTRENADORES");

    /*  Creo lista de entrenadores que va a manejar el Team  */

    this_team->trainers = list_create();

    /*  Creo la lista de objetivos globales que va a manejar el Team */

    this_team->global_objective = list_create();

    /*  Creo un puntero a estructura del tipo Trainer para ir creando cada entrenador leído por archivo de configuración. 
        Estas estructuras se van apuntando en nodos de una lista definida en la estructura del Team como t_list *trainers     */
    Trainer *entrenadores;

    /* -------------- From configuration file to list --------------------- */

    for (int i = 0; *(pos_trainers_to_array + i) != NULL; i++)
    {

        entrenadores = malloc(sizeof(Trainer));

        char **posicion = string_split(*(pos_trainers_to_array + i), "|");
        entrenadores->actual_position.x_ = atoi(*posicion);
        entrenadores->actual_position.y_ = atoi(*(posicion + 1));
        entrenadores->actual_status = NEW;
        entrenadores->trainer_id = i;
        entrenadores->thread_id = 0;
        free(*(posicion));
        free(*(posicion + 1));

        char **mochila = string_split(*(pok_in_bag_to_array + i), "|");
        entrenadores->bag = list_create();
        for (int j = 0; *(mochila + j) != NULL; j++)
            list_add(entrenadores->bag, *(mochila + j));

        char **objetivos = string_split(*(trainers_obj_to_array + i), "|");
        entrenadores->personal_objective = list_create();
        for (int k = 0; *(objetivos + k) != NULL; k++)
            list_add(entrenadores->personal_objective, *(objetivos + k));

        /*  Añado el entrenador creado, ya cada uno con su lista bag y lista de objetivos, a la lista de entrenadores */
        list_add(this_team->trainers, entrenadores);

        /*  Añado los objetivos de cada entrenador a la lista de objetivos globales */
        list_add_all(this_team->global_objective, entrenadores->personal_objective);

        /*  Free the unused memory generated by string_split function from commons library   */
        free(posicion);
        free(mochila);
        free(objetivos);
    }

    /*  Free the unused memory generated by string_split function from commons library   */
    free_split(pos_trainers_to_array);
    free_split(pok_in_bag_to_array);
    free_split(trainers_obj_to_array);

    /* In order to avoid subsequent calls to list size, we store the initial value, as it's supposed to only decrease   */
    this_team->team_size = list_size(this_team->trainers);
}

// ============================================================================================================
//                               ***** Funciones parar liberar listas *****
// ============================================================================================================

void Team_destroy_trainers_and_objective(Team *this_team)
{
    list_destroy_and_destroy_elements(this_team->trainers, _trainer_destroy);
    list_destroy(this_team->global_objective);
}

void free_split(char **string)
{
    for (int i = 0; *(string + i) != NULL; i++)
        free(*(string + i));
    free(string);
}

void _borrar_string(void *string)
{
    free(string);
}

void _trainer_destroy(void *trainer)
{

    list_destroy_and_destroy_elements(((Trainer *)trainer)->personal_objective, _borrar_string);
    list_destroy_and_destroy_elements(((Trainer *)trainer)->bag, _borrar_string);

    free(trainer);
}

// ============================================================================================================
//                               ***** Funciones parar liberar conexiones *****
// ============================================================================================================

void Team_destroy_connections(void *this_team)
{
    _borrar_string(((Team *)this_team)->broker_IP);
    _borrar_string(((Team *)this_team)->broker_port);
    _borrar_string(((Team *)this_team)->planning_algorithm);
}

// ============================================================================================================
//                               ***** Funciones parar imprimir listas (sólo para testear) *****
// ============================================================================================================

void _print_Trainer_list(void *elemento)
{
    puts("\n--TRAINER--");
    t_list *mochila = ((Trainer *)elemento)->bag;
    list_iterate(mochila, _print_Pokemon_caugth);
    t_list *objetivos = ((Trainer *)elemento)->personal_objective;
    list_iterate(objetivos, _print_Objective);
    printf("Thread ID: %d\n", ((Trainer *)elemento)->thread_id);
    puts("--END--");
}

void _print_Pokemon_caugth(void *elemento)
{
    printf("Atrapado: %s\n", (char *)elemento);
}

void _print_Objective(void *elemento)
{
    printf("Objetivo: %s\n", (char *)elemento);
}

void Team_print_gconfig(void *this_team)
{
    puts("\n========================= GLOBAL CONFIGURATION ==============================");
    printf("TIEMPO_RECONEXION= %d\n", ((Team *)this_team)->reconnection_time);
    printf("RETARDO_CICLO_CPU= %d\n", ((Team *)this_team)->cpu_cycle);
    printf("ALGORITMO_PLANIFICACION= %s\n", ((Team *)this_team)->planning_algorithm);
    printf("QUANTUM= %d\n", ((Team *)this_team)->quantum);
    printf("ESTIMACION_INICIAL= %d\n", ((Team *)this_team)->initial_estimation);
    printf("ALPHA= %2f\n", ((Team *)this_team)->alpha);
    printf("IP_BROKER= %s\n", ((Team *)this_team)->broker_IP);
    printf("PUERTO_BROKER= %s\n", ((Team *)this_team)->broker_port);
    puts("=============================================================================");
}
void Team_print_trainers(void *element)
{

    puts("\n========================= Trainer CONFIGURATION ==============================");
    list_iterate(((Team *)element)->trainers, _print_Trainer_list);
    puts("=============================================================================");
}
// ============================================================================================================
//                               ***** Función parar cargar las configuraciones globales *****
// ============================================================================================================

void Team_load_global_config(Team *this_team)
{

    this_team->reconnection_time = config_get_int_value(this_team->team_config, "TIEMPO_RECONEXION");
    this_team->cpu_cycle = config_get_int_value(this_team->team_config, "RETARDO_CICLO_CPU");
    this_team->planning_algorithm = strcpy(this_team->planning_algorithm, config_get_string_value(this_team->team_config, "ALGORITMO_PLANIFICACION"));
    this_team->quantum = config_get_int_value(this_team->team_config, "QUANTUM");
    this_team->initial_estimation = config_get_int_value(this_team->team_config, "ESTIMACION_INICIAL");
    this_team->alpha = config_get_double_value(this_team->team_config, "ALPHA");
    this_team->broker_IP = strcpy(this_team->broker_IP, config_get_string_value(this_team->team_config, "IP_BROKER"));
    this_team->broker_port = strcpy(this_team->broker_port, config_get_string_value(this_team->team_config, "PUERTO_BROKER"));

    config_destroy(this_team->team_config);
}
