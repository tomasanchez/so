#ifndef DBMSG_H
#define DBMSG_H

#include <dbcore.h>

// Para el uso de los tipos de datos uint32_t
#include <inttypes.h>

//*** Paquete que se envia por socket ***
//    -------------------------------
typedef struct
{
	uint32_t buff_size;
	void* buffer;
} db_package;

//*** Par Coordenado en el Mundo ***
//    --------------------------
typedef struct
{
	uint32_t x_pos;
	uint32_t y_pos;
} db_world_pos;

//*** Estructura de los mensajes ***
//    --------------------------
struct db_msg_new
{
	db_world_pos        pos;
	uint32_t			amount;
	uint32_t            name_length;
	char*               name;
};

struct db_msg_localized
{
	uint32_t        id_corr;
	uint32_t        name_length;
	uint32_t        pos_length;
	char*           name;
	db_world_pos*   positions;
};

struct db_msg_get
{
	uint32_t    name_length;
	char*       name;
};

struct db_msg_appeard
{
	db_world_pos    pos;
	uint32_t        name_length;
	char*           name;
};

struct db_msg_catch
{
	uint32_t        id_corr;
	db_world_pos    pos;
	uint32_t        name_length;
	char*           name;
};

struct db_msg_caught
{
	uint32_t    id_corr;
	uint32_t    is_caught;
};

typedef struct db_msg_new*              db_msg_new_ptr;
typedef struct db_msg_localized*        db_msg_localized_ptr;
typedef struct db_msg_get*              db_msg_get_ptr;
typedef struct db_msg_appeard*          db_msg_appeard_ptr;
typedef struct db_msg_catch*            db_msg_catch_ptr;
typedef struct db_msg_caught*           db_msg_caught_ptr;

//*** Tipos de mensajes ***
//    -----------------
typedef enum
{
	NEW_POCKEMON,
	LOCALIZED_POCKEMON,
	GET_POCKEMON,
	APPEARD_POCKEMON,
	CATCH_POCKEMON,
	CAUGHT_POCKEMON
} db_msg_type;

/*
 * @Parametros:
 * ------------
 *
 *              void*   msg         ----->  puntero a con el mensaje a seralizar
 *        db_msg_type   type        ----->  tipo de mensaje.
 *          uint32_t*   buff_size   -----> contendra el tamaño del buffer creado.
 *
 * @Retorna: un puntero al espacio de memoria del mensaje seralizado.
 * ---------
 */
void* db_serialize_msg(const void* msg, db_msg_type type, uint32_t* buff_size) DB_NON_NULL(1, 3);

/*
 * @Parametros:
 * ------------
 *            const void* buffer  -----> puntero con un mensaje serializado (sin el opcode)
 * 
 * @Retorna: un puntero a una estructura de mensaje.
 * ---------
 */
void* db_deserialize_msg(const void* buffer, db_msg_type msg_type) DB_NON_NULL(1);


/*
 * @Parametros:
 * ------------
 *               void* msg  -----> puntero a una estructura de mensaje
 *             db_msg_type  -----> tipo de mensaje.
 */
void db_free_msg(void* msg, db_msg_type type) DB_NON_NULL(1);

db_error db_package_msg(db_package* result, const void* msg, db_msg_type msg_type) DB_NON_NULL(1, 2);
/*
 * @Parametros:
 * ------------
 *
 *                const char*   name    ----->  nombre del pockemon.
 *              db_world_pos    pos     ----->  coordenadas del pockemon.
 *                  uint32_t    amount  ----->  cantidad de pockemons que aparecieron en estas coordenadas.
 *
 * @Retorna: un nuevo paquete de mensaje db_msg_new_ptr, o NULL en caso de error.
 * ---------
 */
db_msg_new_ptr db_create_msg_new(const char* name, db_world_pos pos, uint32_t amount) DB_NON_NULL(1);

/*
 * @Parametros:
 * ------------
 *
 *              const char*      name       ----->  nombre del pockemon.
 *            db_world_pos*      array_pos  ----->  coordenadas donde se localizo el pockemon.
 *                 uint32_t      pos_length ----->  tamaño del array de posiciones.
 *                 uint32_t      id_corr    ----->  id correlativo.
 *
 * @Retorna: un nuevo paquete de mensaje db_msg_localized_ptr, o NULL en caso de error.
 * ---------
 */
db_msg_localized_ptr db_create_msg_localized(const char* name, db_world_pos* array_pos, uint32_t pos_length, uint32_t id_corr) DB_NON_NULL(1, 2);

/*
 * @Parametros:
 * ------------
 *
 *                const char*  name  ----->  nombre del pockemon.
 *
 * @Retorna: un nuevo paquete de mensaje db_msg_get_ptr, o NULL en caso de error.
 * ---------
 */
db_msg_get_ptr db_create_msg_get(const char* name) DB_NON_NULL(1);

/*
 * @Parametros:
 * ------------
 *
 * 				const char*		name	----->	nombre del pockemon.
 * 				db_world_pos	pos		----->	coordenadas donde aparecio el pockemon.
 *
 * @Retorna: un nuevo paquete de mensaje db_msg_new_ptr, o NULL en caso de error.
 * ---------
 */
db_msg_appeard_ptr db_create_msg_appeard(const char* name, db_world_pos pos) DB_NON_NULL(1);

/*
 * @Parametros:
 * ------------
 *
 *               const char*    name   ----->  nombre del pockemon.
 *              db_world_pos    pos    ----->  coordenadas donde se busca capturar al pockemon.
 *
 * @Retorna: un nuevo paquete de mensaje db_msg_new_ptr, o NULL en caso de error.
 * ---------
 */
db_msg_catch_ptr db_create_msg_catch(const char* name, db_world_pos pos) DB_NON_NULL(1);

/*
 * @Parametros:
 * ------------
 *
 *              uint32_t     is_caught  ----->  1 si se pudo caputrar, de lo contrario 0.
 *              uint32_t     id_corr    ----->  id correlativo.
 *
 * @Retorna: un nuevo paquete de mensaje db_msg_new_ptr, o NULL en caso de error.
 * ---------
 */
db_msg_caught_ptr db_create_msg_caught(uint32_t is_caught, uint32_t id_corr);

#endif
