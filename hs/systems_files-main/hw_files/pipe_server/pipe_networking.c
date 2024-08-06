#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "pipe_networking.h"

#define READ 0
#define WRITE 1
#define RESPONSE "Recieved"

/*=========================
  server_setup
  args:

  creates the WKP (upstream) and opens it, waiting for a
  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() { 
  mkfifo(WKP, 0777);
  int from_client = open(WKP, O_RDONLY );
  remove(WKP);
  return from_client;
}

/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  char pipeName[HANDSHAKE_BUFFER_SIZE];
  read(from_client, pipeName, HANDSHAKE_BUFFER_SIZE);
  int to_client  = open(pipeName, O_WRONLY);
  char acknow[HANDSHAKE_BUFFER_SIZE] = ACK;
  write(to_client, acknow, HANDSHAKE_BUFFER_SIZE);
  close(to_client);
  to_client = open(pipeName, O_RDONLY);
  read(to_client, acknow, HANDSHAKE_BUFFER_SIZE);
  if(strcmp(acknow, RESPONSE) == 0){
    printf("Connected successfully with client %s \n", pipeName);
  }else{
    printf("ERROR - Failed to connect to client\n");
  }
  return to_client;
}


/*=========================
  server_handshake
  args: int * to_client
lvim
  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptsongor to the downstream pipe.
So we dont need
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = server_setup();
  while(1){
    if(!fork()){
      *to_client = server_connect(from_client);
      exit(0);
    }
    close(from_client);
    from_client = server_setup();
  }

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char pipeName[HANDSHAKE_BUFFER_SIZE];
  sprintf(pipeName, "%d", getpid());
  mkfifo(pipeName, 0777);

  int from_server = open(WKP, O_WRONLY);
  write(from_server, pipeName, HANDSHAKE_BUFFER_SIZE);
  close(from_server);
  
  char msg[HANDSHAKE_BUFFER_SIZE];
  char respo[HANDSHAKE_BUFFER_SIZE] = RESPONSE;
  int from_client = open(pipeName, O_RDONLY);
  read(from_client, msg, HANDSHAKE_BUFFER_SIZE);
  if (strcmp(msg, ACK)){
    printf("Wrong response\n");
  }
  close(from_client);

  from_client = open(pipeName, O_WRONLY);
  write(from_client, respo, HANDSHAKE_BUFFER_SIZE);
  close(from_client);
  remove(pipeName);
  printf("Yes the server exist\n");
  return from_server;

}
