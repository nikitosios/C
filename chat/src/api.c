#include "api.h"

void *output_packages(void *parameters)
{
	int sockt = *(int *) parameters;
	char message[2000];

	while (1) {
		printf("Вы:\n");
		for (int o = 0; o < sizeof(message); o++)
			if ((message[o] = getchar()) == 0)
				break;
	
		//Send some data
		if(send(sockt, message, sizeof(message), 0) < 0)
		{
			puts("Send failed");
			exit(1);
		}
		message[0] = 0;
	}
}

static void *input_read (void *socket)
{
	int sockett = *(int *) socket;
	char message[2000];

	while (1) {
		printf("Вы:\n");
		for (int o = 0; o < sizeof(message); o++)
			if ((message[o] = getchar()) == '\0')
				break;
		write(sockett, message, strlen(message));
		message[0] = '\0';
	}

	return NULL;
}

void send_to_all(char *msg, int sock)
{
	extern int *socks;

	for (int i = 0; i < ncon; ++i)
		if (socks[i] != sock)
			write(socks[i], msg, strlen(msg));
	return;
}

/* this function will handle connection for each client */
void *connection_handler (void *socket_desc)
{
	const char disconnect_str[] = { '\a', 0 };

	int sock = *(int *)socket_desc;
	int *new_sock = malloc(1);
	*new_sock = sock;
	int read_size;
	char client_message[2000], nickname[21];
	pthread_t input_packages;

	if (recv(sock, nickname, 21, 0) > 0)
		printf("%s connected.\n", nickname);

	//Receive a message from client
	while ((read_size = recv(sock, client_message, 2000, 0)) > 0
			&& client_message[0] != '\a' && client_message[1] != '\0'
			&& read_size > 1)
	{
		for (int o = 0; o < sizeof(client_message); o++)
			if (client_message[o] == '\0')
				break;
			else
				putchar(client_message[o]);
		client_message[0] = '\0';
		printf("---------------------\n");
		send_to_all(client_message, sock);
	}

	printf("%s disconnected.\n", nickname);

	//Free the socket pointer
	free(socket_desc);

	return 0;
}
