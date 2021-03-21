/**
 * connection.h
 * 
 * Conecctivity exporting functions
 * 
 * @file This file describes the connection related functions.
 * @author Tomás A. Sánchez
 * @since 03.21.2021
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Connects to the given IP and PORT.
 * 
 * @function
 * @public
 * @param iv_ip the IP to connect
 * @param iv_port the PORT to listen
 * @returns ev_socket_client - the file descriptor or -1 if error
 */
int connect_to(char *, char *);