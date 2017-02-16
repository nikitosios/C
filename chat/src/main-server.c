#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "api.h"

int main_server(int argc, char *argv[])
{
    int socket_desc, new_socket, c, *new_sock, server_port;
	struct sockaddr_in server, client;

	server_port = 31285;
	for (int i = 1; i < argc; ++i)
	{
		if (!strncmp(argv[i], "--port=", 7))
		{ server_port = atoi(argv[i] + 7);
			printf("%s\n", argv[i]);
		}
	}

	/* create socket */
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	/* prepare the sockaddr_in structure */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(server_port);
	
	/* bind */
	printf("Port %i, binding...\n", server_port);
	if (bind(socket_desc, (struct sockaddr*) &server, sizeof server) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");

	/* listen */
	listen(socket_desc, 2);

	/* accept and incoming connection */
	c = sizeof(struct sockaddr_in);
	while ((new_socket = accept(socket_desc, (struct sockaddr*) &client, (socklen_t*) &c)))
	{
		pthread_t sniffer_thread;
		new_sock = malloc(sizeof new_socket);
		*new_sock = new_socket;

		pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock);
	}

	return 0;
}
