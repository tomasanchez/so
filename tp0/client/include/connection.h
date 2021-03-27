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

/**
 * Disconnects the given socket
 * 
 * @function
 * @public
 * @param iv_socket the socket to free its connection
 * @return the socket close return
 */
int disconnect(int);

/**
 * Tells if is connected to the server
 * @function
 * @public
 * @returns 0 if not connected
 */
int is_connected(void);

/**
 * Tells wether there is a message or not.
 * 
 * @param iv_message the message to be sent
 * @returns 0 if no message
 */
int has_message(char *);

/**
 * Sends a message to that socket
 * 
 * @function
 * @public
 * @param iv_message the stream to be sent
 * @param iv_socket the socket file descriptor
 * @returns the amount of bytes sent
 */
ssize_t send_message(char *, int);