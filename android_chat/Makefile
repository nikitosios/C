CC=gcc
CFLAGS=-Wall
LDFLAGS=-lpthread
SOURCES=client.c server.c
EXE1=client
EXE2=server
all: $(SOURCES) $(EXE1) $(EXE2)
$(EXE1):
	mkdir -p chat
	$(CC) $(CFLAGS) -o chat/$(EXE1) client.c $(LDFLAGS)
	echo 'Press Enter and Ctrl+D to send your message.' > chat/README.txt
	echo 'Press Ctrl+C to disconnect.' >> chat/README.txt
	echo 'You can specify IP:port as argument to the client program.' >> chat/README.txt
	echo 'For example: ./client 192.168.1.1:8888' >> chat/README.txt
	echo '------------------------------------' >> chat/README.txt
	echo 'Нажмите Enter и Ctrl+D чтобы отправить сообщение.' >> chat/README.txt
	echo 'Нажмите Ctrl+C чтобы отключиться.' >> chat/README.txt
	echo 'Вы можете указать IP:порт сервера в качестве аргумента клиентской программе.' >> chat/README.txt
	echo 'К примеру: ./client 192.168.1.1:8888' >> chat/README.txt
$(EXE2):
	mkdir -p chat
	$(CC) $(CFLAGS) -o chat/$(EXE2) server.c $(LDFLAGS)
	echo 'You can specify port on which this server will listen' > chat/SERVER_README.txt
	echo 'as argument for the server program.' >> chat/SERVER_README.txt
	echo 'For example: ./server 8888' >> chat/SERVER_README.txt
	echo '--------------------------------------' >> chat/SERVER_README.txt
	echo 'Вы можете указать порт, на котором будет слушать сервер' >> chat/SERVER_README.txt
	echo 'как аргумент серверной программе.' >> chat/SERVER_README.txt
	echo 'К примеру: ./server 8888' >> chat/SERVER_README.txt
clean:
	rm -r chat
