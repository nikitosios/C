#include "api.h"

void* output_packages(void* parameters)
{
	int sockt = *(int*)parameters;
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

/* this function will handle connection for each client */
void* connection_handler (void* socket_desc)
{
	const char disconnect_str[] = { '\a', 0 };

	int sock = *(int*)socket_desc;
	int* new_sock = malloc(sizeof(int));
	*new_sock = sock;
	int read_size;
	char client_message[2000], nickname[21];

	if (locked)
	{
		puts("I'm busy.");
		return 0;
	}

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
	}

	printf("%s disconnected.\n", nickname);
	locked == 0;

	//Free the socket pointer
	free(socket_desc);

	return 0;
}
