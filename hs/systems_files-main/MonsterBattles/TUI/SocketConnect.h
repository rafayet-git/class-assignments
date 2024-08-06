#ifndef SOCKETCONNECT_H
#define SOCKETCONNECT_H
#include <sys/socket.h>
/* 
 * A struct representing specific socket information for the client/server.
 *
 * @note fdAccess should be the result of accept() for a server connection, clients 
 * use the same value as listen_socket.
 *
 * @data isServer - checks if the program is a server or a client.
 * @data fdAccess - file descriptor to be used for socket reading and writing
 * @data listen_socket - the socket file descriptor used by the program.
 * @data client_address - to be used for the server accept
 * @data sock_size - to be used for the server accept
 * @data hints, results - socket info created when creating a socket
 */
typedef struct{
  int isServer;
  int fdAccess; // server = accept(), client = listen_socket
  int listen_socket;
  struct sockaddr_storage client_address;
  socklen_t sock_size;
  struct addrinfo *hints;
  struct addrinfo *results;
} AddressInf;

/*
 * Sets up socket connection for the program
 *
 * @data addy - struct to store sit's shit anywaocket information
 * @data ipaddress - IP address to be used for connection
 * @data portnum - Port number to be used for connection
 */
void create_socket(AddressInf *addy, char *ipaddress, char *portnum, char is_server);

/* 
 * Enables the server to recieve information from a client.  
 *
 * @data server - struct to store socket information
 */
int server_recieve_connection(AddressInf *server);

/*
 * Enables the client to recieve information from a server.
 *
 * @data_server - struct to store socket information
 */
int client_make_connection(AddressInf *client);

/*
 * Allows the program to write data to a socket
 *
 * @data sok - struct to store socket information
 * @data str - data pointer that will be written to socket
 * @data len - bytes to write from str to the socket
 */
int socket_writedata(AddressInf *sok, void *str, int len);

/*
 * Allows the program to read data from a socket
 *
 * @data sok - struct to store socket information
 * @data str - data to read from the socket
 * @data len - bytes to write from the socket to str 
 */
int socket_readdata(AddressInf *sok, void *str, int len);

/*
 * Frees the allocated memory of struct addrinfo
 *
 * @data inform - struct for socket information to be freed
 *
 */
void freeall(AddressInf *inform);


#endif
