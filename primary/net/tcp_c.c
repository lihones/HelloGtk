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
int port = 9001;

#define BUFFER_SIZE 4096

void tcp_client_main()
{
	struct hostent* host;
	if ((host = gethostbyname(hostStr)) == NULL) {
		return ;
	}
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		return;
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9001);
	servAddr.sin_addr = *((struct in_addr*)host->h_addr);
	if (connect(fd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
		return;
	}

	char chunk[2048];
	memset(chunk, 0, 2048);
	sprintf(chunk, "%s", "i'm tcp client.");
	send(fd, chunk, strlen(chunk), 0);
	printf("send: %s\n", chunk);

	int recvTotal = 0, recvLen = 0;
	char buffer[BUFFER_SIZE];
	char *response = NULL;
	while ((recvLen = recv(fd, buffer, BUFFER_SIZE, 0)) > 0) {
		if (response == NULL) {
			recvTotal = recvLen;
			response = (char*)malloc(recvTotal);
			if (response == NULL) {
				break;
			}
			memcpy(response, buffer, recvLen);
		} else {
			response = (char*)realloc(response, recvTotal+recvLen);
			if (response == NULL) {
				break;
			}
			memcpy(response + recvTotal, buffer, recvLen);
			recvTotal += recvLen;
		}
	}
	if(response != NULL && recvTotal > 0) {
		response = realloc(response, recvTotal + 1);
		response[recvTotal] = '\0';
		printf("recv: %s\n", response);
		free(response);
	}

	close(fd);
}

int main(int argc, char* argv[])
{
	tcp_client_main();

	return 0;
}
