#include "api.h"

int main_server(int argc, char *argv[])
{
    int socket_desc, new_socket, c, *new_sock, server_port, ncon;
	int *socks, con = 0;
	struct sockaddr_in server, client;

	if (argc == 2)
		server_port = 31185;
	else server_port = atoi(argv[2]);

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
	if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");

	puts("How many connections?");
	scanf("%i", &ncon);
	socks = calloc(ncon, sizeof(int));

	/* listen */
	listen(socket_desc, ncon);

	/* accept and incoming connection */
	c = sizeof(struct sockaddr_in);
	while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c)))
	{
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = new_socket;
		socks[con] = new_socket;

		pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock);
		++con;
	}

	return 0;
}
