#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <pthread.h> //multithread
#include <stdlib.h>

const char stdip[] = "176.122.105.83";
const unsigned short stdport = 31184;

void *output_packages (void *parameters);

int square (int num, int ex) {
	int res = 1;

	for (int i = 0; i < ex; i++)
		res *= num;
	return res;
}

int main (int argc, char *argv[])
{
	int sock;
	char server_reply[2000];
    struct sockaddr_in server;
    char c;

    //Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr(stdip);
	server.sin_family = AF_INET;
	server.sin_port = htons(stdport);

	//Connect to remote server
	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}
	puts("Connected");

	//output packages
	pthread_t oPacks;
	pthread_create(&oPacks, NULL, output_packages, (void *) &sock);

	while (1)
	{
		//Receive a reply from the server
		if(recv(sock, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
			break;
		}

		printf("----------------------\nНикита Кот:\n");
		for (int o = 0; o < sizeof(server_reply); o++)
			if (server_reply[o] == '#')
				break;
			else
				putchar(server_reply[o]);
		server_reply[0] = '#';
		printf("----------------------\n");
	}

	close(sock);
	return 0;
}

void *output_packages (void * parameters)
{
	int sockt = *(int *) parameters;
	char message[2000];

	while (1) {
		printf("Вы:\n");
		for (int o = 0; o < sizeof(message); o++)
			if ((message[o] = getchar()) == '#')
				break;
	
		//Send some data
		if(send(sockt, message, sizeof(message), 0) < 0)
		{
			puts("Send failed");
			exit(1);
		}
		message[0] = '#';
	}
}
