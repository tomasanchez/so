#ifndef DBCONN_H
#define DBCONN_H

#include <dbcore.h>

#include <inttypes.h>
#include <netdb.h>

/*
 * @Parametros:
 *                 int*     result   ----->  puntero donde se guardara el socket del servidor.
 *          const char*     host     ----->  string con el nombre o ip del servidor.
 *          const char*     service  ----->  string con el puerto a utilizar.
 *                  int     ipv      ----->  version del protocolo ip a usar (AF_INET | AF_INET6).
 *                  int     flags 	 ----->  bit_field con opciones (AI_PASSIVE, AI_CANONNAME, etc).
 *                  int     socktype ----->  tipo de socket (SOCK_STREAM | SOCK_DATAGRAM).
 *                  int     backlog  ----->  cantidad de solicitudes que puede dejar en cola.
 *
 * @Retorna: QS_SUCCESS en caso de que se haya podido crear y bindear el socket. En caso
 * contrario puede devolver uno de los siguientes errores, y result contendra un socket invalido:
 *
 *                  QS_LOOK_UP_ERROR ----->  no se pudo obtener informacion sobre el host o servicio especificado.
 *                  QS_SOCKET_ERROR  ----->  no se pudo crear el socket o bindearlo.
 *                  QS_LISTEN_ERROR  ----->  el socket no pudo quedar a la escucha del puerto.
 *
 */
db_error db_create_server(int* result, const char* host, const char* service, int ipv, int flags, int socket_type, int backlog);

/*
 * @Parametros:
 *                  int*    result   ----->  puntero donde se guardara el socket del cliente.
 *           const char*    host     ----->  string con el nombre o ip del servidor a conectarse.
 *           const char*    service  ----->  string con el puerto a utilizar.
 *                  int     ipv      ----->  version del protocolo ip a usar (AF_INET | AF_INET6).
 *                  int     flags    ----->  bit_field con opciones (AI_PASSIVE, AI_CANONNAME, etc).
 *                  int	    socktype ----->  tipo de socket (SOCK_STREAM | SOCK_DATAGRAM).
 *
 * @Retorna: QS_SUCCESS en caso de que se haya podido crear y conectar el socket cliente con el servidor.
 * En caso contrario puede devolver uno de los siguientes errores, y result contendra un socket invalido:
 *
 *                  QS_LOOK_UP_ERROR ----->  no se pudo obtener informacion sobre el host o servicio especificado.
 *                  QS_SOCKET_ERROR  ----->  no se pudo crear el socket.
 *                  QS_CONN_ERROR    ----->  no se pudo conectar al servidor.
 *
 */
db_error db_create_client(int* result, const char* host, const char* service, int ipv, int flags, int socket_type);

/*
 * @Parametros:
 *                   int     server	 ----->   socket del servidor.
 *                   int*    client  ----->   puntero que contendra el un socket para el cliente.
 *
 * @Retorna: QS_SUCCESS en caso de que se haya aceptado una conexion. En caso contrario QS_LISTEN_ERROR.
 */
db_error db_accept(int server, int* client) DB_NON_NULL(2);

/*
 * @Parametros:
 *                  int     dest    ----->   socket para enviar los daots.
 *           cosnt void*    data    ----->   buffer con los datos a enviar.
 *         unsigned int     size    ----->   tamaño del buffer.
 *
 * @Retoran: la cantidad de bytes enviados, o -1 en caso de error.
 */
int db_send(int dest, const void* data, unsigned int size) DB_NON_NULL(2);

/*
 * @Parametros:
 *                  int      src    ----->    socket para recibir los daots.
 *                 void*     data   ----->    buffer donde se recibiran los datos.
 *          unsigned int     size   ----->	  tamaño del buffer.
 *
 * @Retoran: la cantidad de bytes recibidos, o -1 en caso de error.
 */
int db_recv(int src, void* data, unsigned int size) DB_NON_NULL(2);

/*
 * @Parametros:
 *                  int      sock   ----->    socket que se va a cerrar.
 *                  int      modo   ----->    modo de cierre.
 */
void db_close_socket(int sock, int mode);

#endif
