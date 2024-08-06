#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>

#include "SocketConnect.h"
#include "StyleChar.h"

void create_socket(AddressInf *addy, char *ipaddress, char *portnum, char is_server){
  addy->hints = calloc(1,sizeof(struct addrinfo));
  addy->hints->ai_family = AF_INET;
  addy->hints->ai_socktype = SOCK_STREAM;
  addy->isServer = is_server;
  addy->results = NULL;
  if (addy->isServer)addy->hints->ai_flags = AI_PASSIVE;
  int addrResults = getaddrinfo(ipaddress, portnum , addy->hints, &(addy->results));  //localhost-127.0.0.1
  addy->listen_socket = socket(addy->results->ai_family, addy->results->ai_socktype, addy->results->ai_protocol);
  int yes = 1;
  if ( setsockopt(addy->listen_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1 ) {
        PRINTF("ERROR - sockopt %s\n", strerror(errno));
        exit(-1);
  }
  if(addy->isServer){
    int bindSocket = bind(addy->listen_socket, addy->results->ai_addr, addy->results->ai_addrlen);
    if (bindSocket == -1){
      PRINTF("ERROR - %s\n",strerror(errno) );
      exit(-2);

    }
    listen(addy->listen_socket, 1);
  }
}

int server_recieve_connection(AddressInf *server){
  if (!server->isServer){
    PRINT("Not a server\n");
    exit(-3);
  }
  server->fdAccess = accept(server->listen_socket, (struct sockaddr *)&(server->client_address), &(server->sock_size));
  if (server->fdAccess == -1){
    PRINTF("ERROR - %s\n", strerror(errno));
    exit(-3);
  }
  return server->fdAccess;
}

int client_make_connection(AddressInf *client){
  if(client->isServer){ //listen_socket to edit
    PRINT("Not a server\n");
    exit(-4);
  }
  client->fdAccess = client->listen_socket;
  int connTest = connect(client->listen_socket, client->results->ai_addr, client->results->ai_addrlen);
  if (connTest!= 0){
    PRINTF("ERROR - %s\n", strerror(errno));
    exit(-4);
  }
  return connTest;
}

int socket_writedata(AddressInf *sok, void *str, int len){
  return write(sok->fdAccess, str, len );
}

int socket_readdata(AddressInf *sok, void *str, int len){
  return read(sok->fdAccess, str, len);
}

void freeall(AddressInf *stuff){
  close(stuff->listen_socket);
  close(stuff->fdAccess);
  free(stuff->hints);
}

