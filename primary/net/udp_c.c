#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

char *hostStr = "127.0.0.1";
int port = 9002;

#define BUFFER_SIZE 4096

void udb_client_main()
{
	struct hostent* host;
	if ((host = gethostbyname(hostStr)) == NULL) {
		return ;
	}
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		return;
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr = *((struct in_addr*)host->h_addr);
	int serv_len = sizeof(servAddr);

	char chunk[2048];
	memset(chunk, 0, 2048);
	sprintf(chunk, "%s", "i'm udp client.");
	sendto(fd, chunk, strlen(chunk), 0, (struct sockaddr*)&servAddr, serv_len);
	printf("send: %s\n", chunk);

	int recvLen = 0;
	char buffer[BUFFER_SIZE];
	recvLen = recvfrom(fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&servAddr, &serv_len);
	if(recvLen > 0) {
		buffer[recvLen] = '\0';
		printf("recv: %s\n", buffer);
	}

	close(fd);
}

int main(int argc, char* argv[])
{
	udb_client_main();

	return 0;
}
