#include <dbconn.h>

//C standar lib
#include <stdlib.h>
#include <string.h>

//Unix lib
#include <arpa/inet.h>
#include <sys/socket.h>

//Macros utilizadas en otra implementacion (capaz no sirvan)
#define CAST_TO_IPV4(sockaddr)	((struct sockaddr_in*)(sockaddr))
#define CAST_TO_IPV6(sockaddr)	((struct sockaddr_in6*)(sockaddr))

db_error db_create_server(int* result, const char* host, const char* service, int ipv, int flags, int socktype, int backlog)
{
	struct addrinfo* server_info;
	struct addrinfo* iterator;
	struct addrinfo hints = {0};

	hints.ai_family = ipv;
	hints.ai_flags = flags;
	hints.ai_socktype = socktype;
	hints.ai_protocol = 0;

	if(getaddrinfo(host, service, &hints, &server_info) < 0)
		return DB_LOOK_UP_ERROR;

//Itero entre los distintos resultados y me quedo con el primero que pueda bindear
	for(iterator = server_info; iterator != NULL; iterator = iterator->ai_next)
	{
		*result = socket(iterator->ai_family, iterator->ai_socktype, iterator->ai_protocol);
		if(*result == -1)
			continue;

		if(bind(*result, iterator->ai_addr, iterator->ai_addrlen) == -1)
		{
			shutdown(*result, 2);
			continue;
		}

		break;
	}

	if(iterator == NULL)
	{
		freeaddrinfo(server_info);
		return DB_SOCKET_ERROR;
	}

	if(listen(*result, backlog) == -1)
	{	
		shutdown(*result, 2);
		freeaddrinfo(server_info);
		return DB_LISTEN_ERROR;
	}

	freeaddrinfo(server_info);

	return DB_SUCCESS;
}

db_error db_create_client(int* result, const char* host, const char* service, int ipv, int flags, int socktype)
{
	struct addrinfo hints = { 0 };
	struct addrinfo* server_info;
	

	hints.ai_family = ipv;
	hints.ai_flags = flags;
	hints.ai_socktype = socktype;
	hints.ai_protocol = 0;

	if(getaddrinfo(host, service, &hints, &server_info) < 0)
		return DB_LOOK_UP_ERROR;

	*result = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(*result == -1)
	{
		freeaddrinfo(server_info);
		return DB_SOCKET_ERROR;
	}

	if(connect(*result, server_info->ai_addr, server_info->ai_addrlen) == -1)
	{
		shutdown(*result, 2);
		freeaddrinfo(server_info);
		return DB_CONN_ERROR;
	}

	freeaddrinfo(server_info);

	return DB_SUCCESS;
}

db_error db_accept(int server, int* client)
{
	struct sockaddr client_info = { 0 };
	unsigned int client_info_size = 0;

	*client = accept(server, &client_info, &client_info_size);

	return (*client == -1) ? DB_ACCEPT_ERROR : DB_SUCCESS;
}

int db_send(int dest, const void* data, unsigned int size)
{
	return send(dest, data, size, 0);
}
int db_recv(int src, void* data, unsigned int size)
{
	return recv(src, data, size, MSG_WAITALL);
}

void db_close_socket(int sock, int mode)
{
	shutdown(sock, mode);
}
