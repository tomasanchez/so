/**
 * connection.c
 * 
 * Conecctivity methods
 * 
 * @file This file describes the connection related functions.
 * @author Tomás A. Sánchez
 * @since 03.21.2021
 */

#include "connection.h"
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

// ============================================================================================================
//                               ***** Connection Definitions *****
// ============================================================================================================

#define ERROR -1

/**
 * Standard operation codes.
 * 
 * @enum
 * @private
 */
typedef enum Opcode
{
    // Message - a standard message
    MSG,
    // Package - other
    PKG,
} opcode_t;

/**
 * A buffer
 * 
 * @class
 * @private
 */
typedef struct Buffer
{
    // The size of stream
    int size;
    // The stream itself
    void *stream;
} buffer_t;

/**
 * Package to be sent.
 * @class
 * @private
 */
typedef struct Package
{
    // Operation code
    opcode_t code;
    // Internal stream buffer
    buffer_t *buffer;
} package_t;

// Global Variable connected - Has value of -1 if not connected
static int gv_connected;

// ============================================================================================================
//                               ***** Private Functions Declarations *****
// ============================================================================================================

/**
 * Instanciates a package.
 * 
 * @function
 * @private
 * @param iv_code the operation code of the new package
 * @param iv_stream the stream to be sent
 * @returns a new package ready to be serialized
 */
static package_t *package_create(opcode_t, char *);

/**
 * Frees memory usage of a package.
 * 
 * @function
 * @private
 * @param is_package the package to be deleted
 */
static void package_destroy(package_t *);

/**
 * Orders a package.
 * 
 * @private
 * @param is_package the package to be serialized
 * @returns the package ready to be sent
 */
static void *package_serialize(package_t *is_package);

/**
 * Gets the bytes which a packages needs to send.
 * 
 * @private
 * @param is_package the package itself
 * @returns the bytes needed for this package.
 */
static int package_get_bytes(package_t *);

/**
 * Instanciates a buffer.
 * 
 * @function
 * @private
 * @param iv_size the size of the stream to be sent
 * @returns a new buffer
 */
static buffer_t *buffer_create(size_t);

/**
 * Frees memory usage of a buffer
 * 
 * @function
 * @public
 * @param is_buffer the buffer to be deleted
 */
static void buffer_destroy(buffer_t *);

// ============================================================================================================
//                               ***** Private Functions Definitions *****
// ============================================================================================================

static package_t *
package_create(opcode_t iv_code, char *iv_stream)
{
    // Exporting Structure package - the new package to be serialized
    package_t *es_package = malloc(sizeof(package_t));

    // Local Variable buffer size - the length of the stream + '\0'
    size_t lv_buffer_size = strlen(iv_stream) + 1;

    es_package->code = iv_code;
    es_package->buffer = buffer_create(lv_buffer_size);

    // Copy the bytes of the stream to the buffer
    memcpy(es_package->buffer->stream, iv_stream, es_package->buffer->size);

    return es_package;
}

static void package_destroy(package_t *is_package)
{
    buffer_destroy(is_package->buffer);
    free(is_package);
}

static void *package_serialize(package_t *is_package)
{
    // Local Variable bytes - the bytes to be sent
    int lv_bytes = package_get_bytes(is_package);

    // Exporting package - the serialized package
    void *e_package = NULL;
    e_package = malloc(lv_bytes);
    // Local variable offset - the offset in the stream
    int lv_offset = 0;

    // Copy parts by bytes, incrementing the offset to obtain a pacakge like
    /**
     *          [ OPCODE ][ SIZE OF MSG ][ MSG ]
     */
    memcpy(e_package + lv_offset, &(is_package->code), sizeof(int));
    lv_offset += sizeof(int);

    memcpy(e_package + lv_offset, &(is_package->buffer->size), sizeof(int));
    lv_offset += sizeof(int);

    memcpy(e_package + lv_offset, is_package->buffer->stream, is_package->buffer->size);
    lv_offset += is_package->buffer->size;

    return e_package;
}

static int package_get_bytes(package_t *is_package)
{
    // The buffer bytes + the opcode bytes + the 'size' bytes
    return is_package->buffer->size + 2 * sizeof(int);
}

static buffer_t *buffer_create(size_t iv_size)
{
    // Exporting Structure buffer - the new buffer of IV_SIZE
    buffer_t *es_buffer = malloc(sizeof(buffer_t));
    es_buffer->size = iv_size;
    es_buffer->stream = malloc(es_buffer->size);
    return es_buffer;
}

static void buffer_destroy(buffer_t *is_buffer)
{
    free(is_buffer->stream);
    free(is_buffer);
}
// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

int connect_to(char *iv_ip, char *iv_port)
{
    // Local Structure hints - the hints for server address info
    struct addrinfo ls_hints;
    // Local Structure server info - a reference for the server address info
    struct addrinfo *ls_server_info;

    // Setting the hints for server
    memset(&ls_hints, 0, sizeof(ls_hints));
    ls_hints.ai_family = AF_UNSPEC;
    ls_hints.ai_socktype = SOCK_STREAM;
    ls_hints.ai_flags = AI_PASSIVE;

    getaddrinfo(iv_ip, iv_port, &ls_hints, &ls_server_info);

    // Exporting Variable client socket - the file descriptor or -1 if error
    int ev_client_socket = socket(ls_server_info->ai_family, ls_server_info->ai_socktype, ls_server_info->ai_protocol);

    // Checks connection
    gv_connected = connect(ev_client_socket, ls_server_info->ai_addr, ls_server_info->ai_addrlen);

    freeaddrinfo(ls_server_info);

    return ev_client_socket;
}

int disconnect(int iv_socket)
{
    return close(iv_socket);
}

int is_connected(void)
{
    return gv_connected != ERROR;
}

int has_message(char *iv_message)
{
    return iv_message != NULL && strlen(iv_message) > 0;
}

ssize_t send_message(char *iv_message, int iv_socket)
{
    // Local Dtructure package - the package to be sent
    package_t *ls_package = package_create(MSG, iv_message);

    // Local stream - the seriealized package, needs a free
    void *l_stream = package_serialize(ls_package);

    // Exporting Variable bytes - the bytes sent or -1 if error
    ssize_t ev_bytes = send(iv_socket, l_stream, package_get_bytes(ls_package), 0);

    free(l_stream);

    package_destroy(ls_package);

    return ev_bytes;
}