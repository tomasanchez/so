#ifndef CONN_H
#define CONN_H

int create_server(const char* host, const char* service);
int connect_to_server(const char* host, const char* service);

int accept_conn(int sd);

int send_data(int sd, const void* data, int size);
int recv_data(int sd, void* data, int size);

void close_connection(int sd);

#endif