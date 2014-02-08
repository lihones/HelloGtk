#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int port = 9002;

#define BUFFER_SIZE 4096

void udp_server_main()
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		printf("socket error\n");
		return;
	}
	
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);
	struct sockaddr_in client_addr;
	int client_addr_len;
	
	if (bind(fd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
		printf("bind error\n");
		return;
	}
	printf("bind succed\n");

	char buffer[BUFFER_SIZE+1];
	int n;
	while(1) {
		n = recvfrom(fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_len);
		if(n <= 0) {
			printf("recvfrom error\n");
			continue;
		}
		buffer[n] = '\0';
		printf("recv: %s\n", buffer);
		char* resp = "i'm udp server";
		sleep(3);
		sendto(fd, resp, strlen(resp), 0, (struct sockaddr*)&client_addr, client_addr_len);
		printf("send: %s\n", resp);
	}

	close(fd);
}

int main(int argc, char* argv[])
{
	udp_server_main();

	return 0;
}
