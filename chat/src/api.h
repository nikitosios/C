#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <pthread.h> //multithread
#include <math.h>

int main_client(int argc, char *argv[]);
int main_server(int argc, char *argv[]);
void *output_packages(void *);
void *connection_handler(void *);
extern char locked;
