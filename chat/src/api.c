#include "api.h"

void *output_packages(void *parameters)
{
	int sockt = *(int *) parameters;
	char message[2000];

	while (1) {
		printf("Вы:\n");
		for (int o = 0; o < sizeof(message); o++)
			if ((message[o] = getchar()) == EOF)
				break;
	
		//Send some data
		if(send(sockt, message, sizeof(message), 0) < 0)
		{
			puts("Send failed");
			exit(1);
		}
		message[0] = EOF;
	}
}

static void *input_read (void *socket)
{
	int sockett = *(int *) socket;
	char message[2000];

	while (1) {
		printf("Вы:\n");
		for (int o = 0; o < sizeof(message); o++)
			if ((message[o] = getchar()) == EOF)
				break;
		write(sockett, message, strlen(message));
		message[0] = EOF;
	}

	return NULL;
}

/* this function will handle connection for each client */
void *connection_handler (void *socket_desc)
{
	//Get the socket descriptor
	int sock = *(int*) socket_desc;
	int *new_sock = malloc(1);
	*new_sock = sock;
	int read_size;
	char client_message[2000];
	pthread_t input_packages;

	//Receive a message from client
	while ((read_size = recv(sock, client_message, 2000, 0)) > 0)
	{
		for (int o = 0; o < sizeof(client_message); o++)
			if (client_message[o] == EOF)
				break;
			else
				putchar(client_message[o]);
		client_message[0] = EOF;
		printf("---------------------\n");
	}

	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	} else if(read_size == -1) {
		perror("recv failed");
	}

	//Free the socket pointer
	free(socket_desc);

	return 0;
}
