#ifndef DBCORE_H
#define DBCORE_H

/*
 * @Descripcion: Se puede colocar al final de la declaracion de una funcion.
 * Indica qué argumentos de la funcion no pueden recibir parametros nulos.
 * En caso de que se le pase un parametro nulo, se mostrara un warning en
 * la compilacion.
 */
#define DB_NON_NULL(...)		__attribute__((nonnull(__VA_ARGS__)))

//Se iba a usar para la implementacion de logs, pero puede que no se utilize
#define DB_PRINT_FORMAT(...)	__attribute__((format (print __VA_ARGS__)))

typedef enum
{
	DB_SUCCESS,
	DB_LOOK_UP_ERROR,
	DB_SOCKET_ERROR,
	DB_CONN_ERROR,
	DB_BIND_ERROR,
	DB_LISTEN_ERROR,
	DB_ACCEPT_ERROR,
	DB_MEM_ERROR
} db_error;

#endif
