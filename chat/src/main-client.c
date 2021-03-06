#include "api.h"

const char *stdport = "31285";

int main_client(int argc, char *argv[])
{
	int sock;
	char server_reply[2000];
    struct sockaddr_in server;
    char server_ip_port[23], c;
	char server_ip[17], server_port[6];
	int server_p = 0;
	char myNickname[21], ch;

	FILE* nicknameFile = fopen("nickname.txt", "r");
	if (nicknameFile == NULL)
	{
		puts("Введите Ваш никнейм (до 20 символов английскими или до 10 русскими):");
		for (int i = 0; i < 20; ++i)
		{
			ch = getchar();
			if (ch == '\n' && i > 0)
			{
				myNickname[i] = '\0';
				break;
			} else {
				myNickname[i] = ch;
			}
		}

		nicknameFile = fopen("nickname.txt", "w");
		for (int i = 0; i < 21; ++i) fputc(myNickname[i], nicknameFile);
		fclose(nicknameFile);
	} else {
		for (int i = 0; i < 21; ++i) myNickname[i] = fgetc(nicknameFile);
		fclose(nicknameFile);
	}

	//Read an IP:port of server
	int i;
	if (argc == 2) {
		puts("Введите IP сервера: ");
		for (i = 0; i < 22; i++) {
			c = fgetc(stdin);
			if (c == '\n')
				break;
			server_ip_port[i] = c;
		}
		server_ip_port[i] = '\0';
	} else 
		memcpy(server_ip_port, argv[2], strlen(argv[2]));
	for (i = 0; server_ip_port[i] != ':' && server_ip_port[i] != '\0'; i++)
		server_ip[i] = server_ip_port[i];
	server_ip[i] = '\0';
	if (server_ip_port[i] == ':') {
		i++;
		for (int o = 0; server_ip_port[i - 1] != '\0'; o++) {
			server_port[o] = server_ip_port[i];
			i++;
		}
	} else
		for (int o = 0; o < sizeof server_port; o++) server_port[o] = stdport[o];
	unsigned char ex = 0;
	for (int o = strlen(server_port) - 1; o != -1; o--) {
		server_p += pow(10, ex) * (server_port[o] - 48);
		ex++;
	}

    //Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(server_p);

	//Connect to remote server
	printf("IP: %s, port: %i, trying...\n", server_ip, server_p);
	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}
	puts("Connected");

	if (send(sock, myNickname, 21, 0) < 0)
	{
		puts("Can't send data.");
		return 1;
	}

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
			if (server_reply[o] == EOF)
				break;
			else
				putchar(server_reply[o]);
		server_reply[0] = EOF;
		printf("----------------------\n");
	}

	close(sock);
	return 0;
}
