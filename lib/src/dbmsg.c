#include <dbmsg.h>

//C standar lib
#include <stdlib.h>
#include <string.h>

// Los define MSG_<TYPE>_FIXED_SIZE contienen el tamaño fijo
// de los mensajes mas los 4 bytes que se deben reservar para
// incluir el codigo de msg.

#define MSG_NEW_FIXED_SIZE             24
#define MSG_LOCALIZED_FIXED_SIZE       20
#define MSG_GET_FIXED_SIZE             12
#define MSG_APPEARD_FIXED_SIZE         20
#define MSG_CATCH_FIXED_SIZE           24
#define MSG_CAUGHT_FIXED_SIZE          18
#define MSG_SUSCRIBE_FIXED_SIZE        8

#define CAST_TO_MSG_CODE(buffer_ptr)            (*((db_msg_type*)(buffer_ptr)))
#define CAST_TO_WORLD_POS(buffer_ptr)           (*((db_world_pos*)(buffer_ptr)))
#define CAST_TO_WORLD_POS_ARRAY(buffer_ptr)     ((db_world_pos*)(buffer_ptr))
#define CAST_TO_UINT32(buffer_ptr)              (*((uint32_t*)(buffer_ptr)))

typedef struct
{
	uint32_t            id;
	db_world_pos        pos;
	uint32_t			amount;
	uint32_t            name_length;
	char*               name;
} db_msg_new_internal;

typedef struct
{
	uint32_t        id;
	uint32_t        id_corr;
	uint32_t        name_length;
	uint32_t        pos_length;
	char*           name;
	db_world_pos*   positions;
} db_msg_localized_internal;

typedef struct
{
	uint32_t    id;
	uint32_t    name_length;
	char*       name;
} db_msg_get_internal;

typedef struct
{
	uint32_t        id;
	db_world_pos    pos;
	uint32_t        name_length;
	char*           name;
} db_msg_appeard_internal;

typedef struct
{
	uint32_t        id;
	uint32_t        id_corr;
	db_world_pos    pos;
	uint32_t        name_length;
	char*           name;
} db_msg_catch_internal;

typedef struct
{
	uint32_t    id;
	uint32_t    id_corr;
	uint32_t    is_caught;
} db_msg_caught_internal;

typedef struct
{
	uint32_t    id;
	db_msg_type msg_type;
} db_msg_suscribe_internal;

// ============================================================================================================
//               ***** Funciones para serializar y deserializar cada uno de los mensajes *****
// ============================================================================================================
static void* db_serialize_msg_new(const db_msg_new_ptr msg, db_msg_type type, uint32_t* buff_size);
static void* db_serialize_msg_localized(const db_msg_localized_ptr msg, db_msg_type type, uint32_t* buff_size);
static void* db_serialize_msg_get(const db_msg_get_ptr msg, db_msg_type type, uint32_t* buff_size);
static void* db_serialize_msg_appeard(const db_msg_appeard_ptr msg, db_msg_type type, uint32_t* buff_size);
static void* db_serialize_msg_catch(const db_msg_catch_ptr msg, db_msg_type type, uint32_t* buff_size);
static void* db_serialize_msg_caught(const db_msg_caught_ptr msg, db_msg_type type, uint32_t* buff_size);
static void* db_serialize_msg_suscribe(const db_msg_suscribe_ptr msg, db_msg_type type, uint32_t* buff_size);

static db_msg_new_ptr db_deserialize_msg_new(const void* buffer);
static db_msg_localized_ptr db_deserialize_msg_localized(const void* buffer);
static db_msg_get_ptr db_deserialize_msg_get(const void* buffer);
static db_msg_appeard_ptr db_deserialize_msg_appeard(const void* buffer);
static db_msg_catch_ptr db_deserialize_msg_catch(const void* buffer);
static db_msg_caught_ptr db_deserialize_msg_caught(const void* buffer);
static db_msg_suscribe_ptr db_deserialize_msg_suscribe(const void* buffer);
// ============================================================================================================
// ============================================================================================================

// ============================================================================================================
//                    ***** Funciones para liberar los recursos utilizados por los msg *****
// ============================================================================================================
static void db_free_msg_new(db_msg_new_ptr msg) DB_NON_NULL(1);
static void db_free_msg_localized(db_msg_localized_ptr msg) DB_NON_NULL(1);
static void db_free_msg_get(db_msg_get_ptr msg) DB_NON_NULL(1);
static void db_free_msg_appeard(db_msg_appeard_ptr msg) DB_NON_NULL(1);
static void db_free_msg_catch(db_msg_catch_ptr msg) DB_NON_NULL(1);
static void db_free_msg_caught(db_msg_caught_ptr msg) DB_NON_NULL(1);
static void db_free_msg_suscribe(db_msg_suscribe_ptr msg) DB_NON_NULL(1);
// ============================================================================================================
// ============================================================================================================

static const char* const MSG_TYPE_STR[] =
{
	"UNKWNOWN",
	"NEW_POCKEMON",
	"LOCALIZED_POCKEMON",
	"GET_POCKEMON",
	"APPEARD_POCKEMON",
	"CATCH_POCKEMON",
	"CAUGHT_POCKEMON",
	"SUSCRIBE"
};


// ============================================================================================================
//                               ***** Implementacion funciones publicas *****
// ============================================================================================================
void* db_serialize_msg(const void* msg, db_msg_type type, uint32_t* buff_size)
{
	switch(type)
	{
	case NEW_POCKEMON:
		return db_serialize_msg_new((const db_msg_new_ptr)msg, type, buff_size);

	case LOCALIZED_POCKEMON:
		return db_serialize_msg_localized((const db_msg_localized_ptr)msg, type, buff_size);

	case GET_POCKEMON:
		return db_serialize_msg_get((const db_msg_get_ptr)msg, type, buff_size);

	case APPEARD_POCKEMON:
		return db_serialize_msg_appeard((const db_msg_appeard_ptr)msg, type, buff_size);

	case CATCH_POCKEMON:
		return db_serialize_msg_catch((const db_msg_catch_ptr)msg, type, buff_size);

	case CAUGHT_POCKEMON:
		return db_serialize_msg_caught((const db_msg_caught_ptr)msg, type, buff_size);
	case SUSCRIBE:
		return db_serialize_msg_suscribe((const db_msg_suscribe_ptr)msg, type, buff_size);
	default:
		return NULL;
	}
}

void* db_deserialize_msg(const void* buffer, db_msg_type msg_type)
{
	switch(msg_type)
	{
	case NEW_POCKEMON:
		return db_deserialize_msg_new(buffer + sizeof(db_msg_type));

	case LOCALIZED_POCKEMON:
		return db_deserialize_msg_localized(buffer + sizeof(db_msg_type));

	case GET_POCKEMON:
	 	return db_deserialize_msg_get(buffer + sizeof(db_msg_type));

	case APPEARD_POCKEMON:
		return db_deserialize_msg_appeard(buffer + sizeof(db_msg_type));

	case CATCH_POCKEMON:
		return db_deserialize_msg_catch(buffer + sizeof(db_msg_type));

	case CAUGHT_POCKEMON:
		return db_deserialize_msg_caught(buffer + sizeof(db_msg_type));

	case SUSCRIBE:
		return db_deserialize_msg_suscribe(buffer + sizeof(db_msg_type));

	default:
		return NULL;
	}
}

void db_free_msg(void* msg, db_msg_type type)
{
	switch(type)
	{
	case NEW_POCKEMON:
		db_free_msg_new(msg);
		break;

	case LOCALIZED_POCKEMON:
		db_free_msg_localized(msg);
		break;

	case GET_POCKEMON:
		db_free_msg_get(msg);
		break;

	case APPEARD_POCKEMON:
		db_free_msg_appeard(msg);
		break;

	case CATCH_POCKEMON:
		db_free_msg_catch(msg);
		break;

	case CAUGHT_POCKEMON:
		db_free_msg_caught(msg);
		break;

	case SUSCRIBE:
		db_free_msg_suscribe(msg);
		break;
	default:
		break;
	}

}

db_error db_pack_msg(db_package* result, const void* msg, db_msg_type msg_type)
{
	result->buffer = db_serialize_msg(msg, msg_type, &result->buff_size);

	return (result->buffer) ? DB_SUCCESS : DB_MEM_ERROR;
}

db_msg_new_ptr db_create_msg_new(uint32_t id, const char* name, db_world_pos pos, uint32_t amount)
{
	db_msg_new_ptr msg = malloc(sizeof(db_msg_new_internal));
	if(msg == NULL)
		return NULL;

	msg->id = id;
	msg->name_length = strlen(name) + 1;
	msg->name = malloc(msg->name_length);
	if(msg->name == NULL)
	{
		free(msg);
		return NULL;
	}
	strcpy(msg->name, name);

	msg->pos = pos;
	msg->amount = amount;

	return msg;
}

db_msg_localized_ptr db_create_msg_localized(uint32_t id, const char* name, db_world_pos* pos_array, uint32_t pos_length, uint32_t id_corr)
{
	db_msg_localized_ptr msg = malloc(sizeof(db_msg_localized_internal));
	if(msg == NULL)
		return NULL;

	msg->id = id;
	msg->name_length = strlen(name) + 1;
	msg->name = malloc(msg->name_length);
	if(msg->name == NULL)
	{
		free(msg);
		return NULL;
	}
	strcpy(msg->name, name);

	msg->pos_length = pos_length;
	msg->positions = malloc(msg->pos_length * sizeof(db_world_pos));
	if(msg->positions == NULL)
	{
		free(msg->name);
		free(msg);
		return NULL;
	}
	memcpy(msg->positions, pos_array, pos_length * sizeof(db_world_pos));

	msg->id_corr = id_corr;

	return msg;
}

db_msg_get_ptr db_create_msg_get(uint32_t id, const char* name)
{
	db_msg_get_ptr msg = malloc(sizeof(db_msg_get_internal));
	if(msg == NULL)
		return NULL;

	msg->id = id;
	msg->name_length = strlen(name) + 1;
	msg->name = malloc(msg->name_length);
	if(msg->name == NULL)
	{
		free(msg);
		return NULL;
	}
	strcpy(msg->name, name);

	return msg;
}

db_msg_appeard_ptr db_create_msg_appeard(uint32_t id, const char* name, db_world_pos pos)
{
	db_msg_appeard_ptr msg = malloc(sizeof(db_msg_appeard_internal));
	if(msg == NULL)
		return NULL;

	msg->id = id;
	msg->name_length = strlen(name) + 1;
	msg->name = malloc(msg->name_length);
	if(msg->name == NULL)
	{
		free(msg);
		return NULL;
	}
	strcpy(msg->name, name);

	msg->pos = pos;

	return msg;
}

db_msg_catch_ptr db_create_msg_catch(uint32_t id, uint32_t id_corr, const char* name, db_world_pos pos)
{
	db_msg_catch_ptr msg = malloc(sizeof(db_msg_catch_internal));
	if(msg == NULL)
		return NULL;

	msg->id = id;
	msg->id_corr = id_corr;
	msg->name_length = strlen(name) + 1;
	msg->name = malloc(msg->name_length);
	if(msg->name == NULL)
	{
		free(msg);
		return NULL;
	}
	strcpy(msg->name, name);

	msg->pos = pos;

	return msg;
}

db_msg_caught_ptr db_create_msg_caught(uint32_t id, uint32_t is_caught, uint32_t id_corr)
{
	db_msg_caught_ptr msg = malloc(sizeof(db_msg_caught_internal));
	if(msg == NULL)
		return NULL;

	msg->id = id;
	msg->is_caught = is_caught;
	msg->id_corr = id_corr;

	return msg;
}

db_msg_suscribe_ptr db_create_msg_suscribe(db_msg_type msg_queue)
{
	if(msg_queue != SUSCRIBE)
	{
		db_msg_suscribe_ptr msg = malloc(sizeof(db_msg_suscribe_internal));
		if(msg)
		{
			msg->msg_queue = msg_queue;
			return msg;
		}
	}

	return NULL;
}

db_world_pos db_create_world_pos(uint32_t x, uint32_t y)
{
	return (db_world_pos){ x, y };
}

const char* db_msg_type_str(db_msg_type msg_type)
{
	return MSG_TYPE_STR[msg_type + 1];
}

bool db_compare_world_pos(db_world_pos pos1, db_world_pos pos2)
{
	return pos1.x_pos == pos2.x_pos && pos1.y_pos == pos2.y_pos;
}

// ============================================================================================================
// ============================================================================================================



// ============================================================================================================
//                              ***** Implementacion funciones privadas *****
// ============================================================================================================


//  ****************************
//  Serialize Message Functions:
//  ****************************

/*
 * Message New Buffer Layout:
 * --------------------------
 *
 * 					| msg_code |    id     |world_coords |   amount  | name_length |       name        |
 * 					------------------------------------------------------------------------------------
 * 					| 4 bytes  |   4 bytes |  8 bytes    |  4 bytes  |   4 bytes   | name_length bytes |
 *
 */
static void* db_serialize_msg_new(const db_msg_new_ptr msg, db_msg_type type, uint32_t* buff_size)
{
	void* buffer = malloc(
		MSG_NEW_FIXED_SIZE +
		msg->name_length
	);

	if(buffer == NULL)
		return NULL;

	*buff_size = 0;
	memcpy(buffer, &type, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->pos.x_pos, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->pos.y_pos, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->amount, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->name_length, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	strcpy(buffer + *buff_size, msg->name);
	*buff_size += msg->name_length;

	return buffer;
}


/*
 * Message Localized Buffer Layout:
 * --------------------------------
 *
 *				  	| msg_code |    id     |id_correlativo | name_length |       name        | pos_length |      positions   |
 *				  	---------------------------------------------------------------------------------------------------------
 *				  	| 4 bytes  |  4 bytes  |   4 bytes     |   4 bytes   | name_length bytes |  4 bytes   | pos_length bytes |
 *
 */
static void* db_serialize_msg_localized(const db_msg_localized_ptr msg, db_msg_type type, uint32_t* buff_size)
{
	void* buffer = malloc(
		MSG_LOCALIZED_FIXED_SIZE +
		msg->pos_length * sizeof(db_world_pos) +
		msg->name_length
	);

	if(buffer == NULL)
		return NULL;

	*buff_size = 0;
	memcpy(buffer, &type, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id_corr, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->name_length, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, msg->name, msg->name_length);
	*buff_size += msg->name_length;
	memcpy(buffer + *buff_size, &msg->pos_length, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, msg->positions, msg->pos_length);
	*buff_size += msg->pos_length * sizeof(db_world_pos);

	return buffer;
}


/*
 * Message Get Buffer Layout:
 * --------------------------
 *
 * 					| msg_code |    id   |name_length |       name        |
 * 					-------------------------------------------------------
 * 					| 4 bytes  | 4 bytes | 4 bytes    | name_length bytes |
 */
static void* db_serialize_msg_get(const db_msg_get_ptr msg, db_msg_type type, uint32_t* buff_size)
{
	void* buffer = malloc(
		MSG_GET_FIXED_SIZE +
		msg->name_length
	);

	if(buffer == NULL)
		return NULL;

	*buff_size = 0;
	memcpy(buffer, &type, sizeof(db_msg_type));
	*buff_size += sizeof(db_msg_type);
	memcpy(buffer + *buff_size, &msg->id, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->name_length, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, msg->name, msg->name_length);
	*buff_size += msg->name_length;

	return buffer;
}


/*
 * Message Appeard Buffer Layout:
 * ------------------------------
 *
 * 					| msg_code |    id     | world_coords | name_lenght |        name       |
 * 					-------------------------------------------------------------
 * 					| 4 bytes  |  4 bytes  |    8 bytes   |   4 bytes   | name_length bytes |
 */
static void* db_serialize_msg_appeard(const db_msg_appeard_ptr msg, db_msg_type type, uint32_t* buff_size)
{
	void* buffer = malloc(
		MSG_APPEARD_FIXED_SIZE +
		msg->name_length
	);

	if(buffer == NULL)
		return NULL;

	*buff_size = 0;
	memcpy(buffer, &type, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->pos.x_pos, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->pos.y_pos, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->name_length, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, msg->name, msg->name_length);
	*buff_size += msg->name_length;

	return buffer;
}


/*
 * Message Catch Buffer Layout:
 * ----------------------------
 *
 *             | msg_code |    id   |   id_corr   | world_pos | name_length |        name       |
 *             ----------------------------------------------------------------------------------
 *             |  4 bytes | 4 bytes |   4 bytes   |  8 bytes  |  4 bytes    | name_length bytes |
 */
static void* db_serialize_msg_catch(const db_msg_catch_ptr msg, db_msg_type type, uint32_t* buff_size)
{
	void* buffer = malloc(
		MSG_CATCH_FIXED_SIZE +
		msg->name_length
	);

	if(buffer == NULL)
		return NULL;

	*buff_size = 0;
	memcpy(buffer, &type, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id_corr, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->pos, sizeof(db_world_pos));
	*buff_size += sizeof(db_world_pos);
	memcpy(buffer + *buff_size, &msg->name_length, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, msg->name, msg->name_length);
	*buff_size += msg->name_length;

	return buffer;
}


/*
 * Message Caught Buffer Layout:
 * -----------------------------
 *
 * 					| msg_code |    id    |  id_correlativo  | is_caught  |
 * 					-------------------------------------------------------
 * 					|  4 bytes |  4 bytes |      4 bytes     |  4 bytes   |
 */
static void* db_serialize_msg_caught(const db_msg_caught_ptr msg, db_msg_type type, uint32_t* buff_size)
{
	void* buffer = malloc(MSG_CATCH_FIXED_SIZE);

	if(buffer == NULL)
		return NULL;

	*buff_size = 0;
	memcpy(buffer, &type, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->id_corr, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);
	memcpy(buffer + *buff_size, &msg->is_caught, sizeof(uint32_t));
	*buff_size += sizeof(uint32_t);

	return buffer;
}

static void* db_serialize_msg_suscribe(const db_msg_suscribe_ptr msg, db_msg_type type, uint32_t* buff_size)
{
	void* buffer = malloc(MSG_SUSCRIBE_FIXED_SIZE);
	if(buffer == NULL)
		return NULL;

	*buff_size = 0;
	memcpy(buffer, &type, sizeof(db_msg_type));
	*buff_size += sizeof(db_msg_type);
	memcpy(buffer + *buff_size, &msg->msg_queue, sizeof(db_msg_type));
	*buff_size += sizeof(db_msg_type);

	return buffer;
}

//  ******************************
//  Deserialize Message Functions:
//  ******************************


/*
 * Message New Buffer Layout:
 * --------------------------
 *
 * 					| msg_code |    id     |  world_coords |   amount  | name_length |       name        |
 * 					--------------------------------------------------------------------------------------
 * 					| 4 bytes  |   4 bytes |    8 bytes    |  4 bytes  |   4 bytes   | name_length bytes |
 *
 */
static db_msg_new_ptr db_deserialize_msg_new(const void* buffer)
{
	int off_set = 0;
	db_msg_new_ptr msg = malloc(sizeof(db_msg_new_internal));

	if(msg)
	{
		msg->id = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->pos = CAST_TO_WORLD_POS(buffer + off_set);
		off_set += sizeof(db_world_pos);
		msg->amount = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->name_length = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		
		msg->name = malloc(msg->name_length);
		if(msg->name)
		{
			strcpy(msg->name, buffer + off_set);
			return msg;
		}

		free(msg);
	}

	return NULL;
}

/*
 * Message Localized Buffer Layout:
 * --------------------------------
 *
 *				  	| msg_code |     id     |  id_correlativo | name_length |       name        | pos_length |      positions   |
 *				  	-------------------------------------------------------------------------------------------------------------
 *				  	| 4 bytes  |  4bytes    |     4 bytes     |   4 bytes   | name_length bytes |  4 bytes   | pos_length bytes |
 *
 */
static db_msg_localized_ptr db_deserialize_msg_localized(const void* buffer)
{
	int off_set = 0;
	db_msg_localized_ptr msg = malloc(sizeof(db_msg_localized_internal));
	
	if(msg)
	{
		msg->id = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->id_corr = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->name_length = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		
		msg->name = malloc(msg->name_length);
		if(msg->name)
		{
			strcpy(msg->name, buffer + off_set);
			off_set += msg->name_length;

			msg->pos_length = CAST_TO_UINT32(buffer + off_set);
			off_set += sizeof(uint32_t);

			msg->positions = malloc(sizeof(db_world_pos) * msg->pos_length);
			if(msg->positions)
			{
				memcpy(msg->positions, buffer + off_set, sizeof(db_world_pos) * msg->pos_length);
				return msg;
			}
		}

		free(msg);
	}

	return NULL;
}

/*
 * Message Get Buffer Layout:
 * --------------------------
 *
 * 					| msg_code |    id     | name_length |       name        |
 * 					---------------------------------------------------------
 * 					| 4 bytes  |  4 bytes  |  4 bytes    | name_length bytes |
 */
static db_msg_get_ptr db_deserialize_msg_get(const void* buffer)
{
	int off_set = 0;
	db_msg_get_ptr msg = malloc(sizeof(db_msg_get_internal));
	
	if(msg)
	{
		msg->id = CAST_TO_UINT32(buffer);
		off_set += sizeof(uint32_t);
		msg->name_length = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->name = malloc(msg->name_length);

		if(msg->name)
		{
			strcpy(msg->name, buffer + off_set);
			return msg;
		}

		free(msg);
	}

	return NULL;
}

/*
 * Message Appeard Buffer Layout:
 * ------------------------------
 *
 * 					| msg_code |    id     | world_coords | name_lenght |        name       |
 * 					-------------------------------------------------------------
 * 					| 4 bytes  |  4 bytes  |    8 bytes   |   4 bytes   | name_length bytes |
 */
static db_msg_appeard_ptr db_deserialize_msg_appeard(const void* buffer)
{
	db_msg_appeard_ptr msg = malloc(sizeof(db_msg_appeard_internal));
	int off_set = 0;

	if(msg)
	{
		msg->id = CAST_TO_UINT32(buffer);
		off_set += sizeof(uint32_t);
		msg->pos.x_pos = CAST_TO_WORLD_POS(buffer + off_set).x_pos;
		msg->pos.y_pos = CAST_TO_WORLD_POS(buffer + off_set).y_pos;
		off_set += sizeof(db_world_pos);
		msg->name_length = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->name = malloc(msg->name_length);

		if(msg->name)
		{
			strcpy(msg->name, buffer + off_set);
			return msg;
		}

		free(msg);
	}

	return NULL;
}

/*
 * Message Catch Buffer Layout:
 * ----------------------------
 *
 *             | msg_code |  id     |   id_corr   | world_pos | name_length |        name       |
 *             ----------------------------------------------------------------------------------
 *             |  4 bytes | 4 bytes |   4 bytes   |  8 bytes  |  4 bytes    | name_length bytes |
 */
static db_msg_catch_ptr db_deserialize_msg_catch(const void* buffer)
{
	db_msg_catch_ptr msg = malloc(sizeof(db_msg_catch_internal));
	uint32_t off_set = 0;

	if(msg)
	{
		msg->id = CAST_TO_UINT32(buffer);
		off_set += sizeof(uint32_t);
		msg->id_corr = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->pos.x_pos = CAST_TO_WORLD_POS(buffer + off_set).x_pos;
		msg->pos.y_pos = CAST_TO_WORLD_POS(buffer + off_set).y_pos;
		off_set += sizeof(db_world_pos);
		msg->name_length = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->name = malloc(msg->name_length);

		if(msg->name)
		{
			strcpy(msg->name, buffer + off_set);
			return msg;
		}

		free(msg);
	}

	return NULL;
}

/*
 * Message Caught Buffer Layout:
 * -----------------------------
 *
 * 					| msg_code |     id   | id_correlativo | is_caught |
 * 					----------------------------------------------------
 * 					|  4 bytes |  4 bytes |    4 bytes     |  4 bytes  |
 */
static db_msg_caught_ptr db_deserialize_msg_caught(const void* buffer)
{
	int off_set = 0;
	db_msg_caught_ptr msg = malloc(sizeof(db_msg_caught_internal));

	if(msg)
	{
		msg->id = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->id_corr = CAST_TO_UINT32(buffer + off_set);
		off_set += sizeof(uint32_t);
		msg->is_caught = CAST_TO_UINT32(buffer + off_set);

		return msg;
	}

	return NULL;
}

static db_msg_suscribe_ptr db_deserialize_msg_suscribe(const void* buffer)
{
	db_msg_suscribe_ptr msg = malloc(sizeof(db_msg_suscribe_internal));
	if(msg)
	{
		msg->msg_queue = CAST_TO_MSG_CODE(buffer);
		return msg;
	}

	return NULL;
}


//  ***********************
//  Free Message Functions:
//  ***********************

static void db_free_msg_new(db_msg_new_ptr msg)
{
	free(msg->name);
	free(msg);
}

static void db_free_msg_localized(db_msg_localized_ptr msg)
{
	free(msg->name);
	free(msg->positions);
	free(msg);
}

static void db_free_msg_get(db_msg_get_ptr msg)
{
	free(msg->name);
	free(msg);
}

static void db_free_msg_appeard(db_msg_appeard_ptr msg)
{
	free(msg->name);
	free(msg);
}

static void db_free_msg_catch(db_msg_catch_ptr msg)
{
	free(msg->name);
	free(msg);
}

static void db_free_msg_caught(db_msg_caught_ptr msg)
{
	free(msg);
}

static void db_free_msg_suscribe(db_msg_suscribe_ptr msg)
{
	free(msg);
}