#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int port = 9001;

#define BUFFER_SIZE 4096

void tcp_server_main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		printf("socket error\n");
		return;
	}
	
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);
	
	if (bind(fd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
		printf("bind error\n");
		return;
	}

	if(listen(fd, 10) != 0) {
		printf("listen error\n");
		return;
	}
	printf("listen:\n");

	int c;
	char buffer[BUFFER_SIZE+1];
	int n;
	while(1) {
		if((c = accept(fd, NULL, NULL)) == -1) {
			printf("accept error\n");
			continue;
		}
		n = recv(c, buffer, BUFFER_SIZE, 0);
		buffer[n] = '\0';
		printf("accept:%d\n%s\n", n, buffer);
		char* resp = "i'm tcp server";
		sleep(3);
		send(c, resp, strlen(resp), 0);
		close(c);
	}

	close(fd);
}

int main(int argc, char* argv[])
{
	tcp_server_main();

	return 0;
}
