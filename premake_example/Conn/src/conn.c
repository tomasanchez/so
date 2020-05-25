#include <conn.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef NULL
    #define NULL (const void*)0
#endif

int create_server(const char* host, const char* server)
{
    struct addrinfo* server_info;
    struct addrinfo* iterator;
    struct addrinfo hints;
    int sd;

    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    if(getaddrinfo(host, server, &hints, &server_info) < 0)
        return -1;

    for(iterator = server_info; iterator != NULL; iterator = iterator->ai_next)
    {
        if((sd = socket(iterator->ai_family, iterator->ai_socktype, iterator->ai_protocol)) == -1)
            continue;

        if(bind(sd, iterator->ai_addr, iterator->ai_addrlen) == -1)
        {
            shutdown(sd, 2);
            continue;
        }

        break;
    }

    return (iterator && listen(sd, 5) != -1) ? sd : -1;
}

int connect_to_server(const char* host, const char* service)
{
    struct addrinfo* server_info;
    struct addrinfo* iterator;
    struct addrinfo hints;

    int sd;

    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    if(getaddrinfo(host, service, &hints, &server_info) < 0)
        return -1;

    for(iterator = server_info; iterator != NULL; iterator = iterator->ai_next)
    {
        if((sd = socket(iterator->ai_family, iterator->ai_socktype, iterator->ai_protocol)) == -1)
            continue;

        if(connect(sd, iterator->ai_addr, iterator->ai_addrlen) == -1)
        {
            shutdown(sd, 2);
            continue;
        }

        break;
    }

    freeaddrinfo(server_info);

    return (iterator) ? sd : -1;
}

int accept_conn(int sd)
{
    struct sockaddr conn_info;
    int conn_info_size;

    return accept(sd, &conn_info, &conn_info_size);
}

int send_data(int sd, const void* data, int size)
{
    return send(sd, data, size, 0);
}

int recv_data(int sd, void* data, int size)
{
    return recv(sd, data, size, 0);
}

void close_connection(int sd)
{
    shutdown(sd, 2);
}