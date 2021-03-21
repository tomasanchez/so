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
    if (connect(ev_client_socket, ls_server_info->ai_addr, ls_server_info->ai_addrlen) == ERROR)
        printf("error");

    freeaddrinfo(ls_server_info);

    return ev_client_socket;
}