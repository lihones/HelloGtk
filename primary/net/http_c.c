#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define TIME_OUT 30

int setSocketTimeOut(int fd, int sendSeconds, int recvSeconds);

void httpGet(char* uri, char** response, unsigned int* responseLen)
{
	if (uri == NULL) {
		return ;
	}

	int uriLen = strlen(uri);
	char hostStr[uriLen];
	char pathStr[uriLen];
	char *hostPtr, *pathPtr;
	hostPtr = strstr(uri, "//");
	if (hostPtr == NULL) {
		return;
	}
	hostPtr += 2;
	pathPtr = strchr(hostPtr, '/');
	if (pathPtr == NULL) {
		int len = strlen(hostPtr);
		memcpy(hostStr, hostPtr, len);
		hostStr[len] = '\0';
		strcpy(pathStr, "/");
	} else {
		int len = strlen(hostPtr) - strlen(pathPtr);
		memcpy(hostStr, hostPtr, len);
		hostStr[len] = '\0';
		strcpy(pathStr, pathPtr);
	}

	struct hostent* host;
	if ((host = gethostbyname(hostStr)) == NULL) {
		return ;
	}
	int fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		return;
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(80);
	servAddr.sin_addr = *((struct in_addr*)host->h_addr);
	if (connect(fd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
		return;
	}

	char chunk[2048];
	memset(chunk, 0, 2048);
	sprintf(chunk,
			"GET %s HTTP/1.1\r\n"
	        "Accept: */*\r\n"
	        "User-Agent: aaa\r\n"
	        "Host: %s\r\n"
	        "Connection: Close\r\n\r\n",
	        pathStr,
	        hostStr);
	send(fd, chunk, strlen(chunk), 0);

	int recvTotal = 0, recvLen = 0;
	char buffer[BUFFER_SIZE];
	*response = NULL;
	while ((recvLen = recv(fd, buffer, BUFFER_SIZE, 0)) > 0) {
		if (*response == NULL) {
			recvTotal = recvLen;
			*response = (char*)malloc(recvTotal);
			if (*response == NULL) {
				break;
			}
			memcpy(*response, buffer, recvLen);
		} else {
			*response = (char*)realloc(*response, recvTotal+recvLen);
			if (*response == NULL) {
				break;
			}
			memcpy(*response + recvTotal, buffer, recvLen);
			recvTotal += recvLen;
		}
	}
	*responseLen = recvTotal;

	close(fd);
}

void httpPost(char* uri, char* data, unsigned int dataLen,
			  char** response, unsigned int* responseLen, char* agent)
{
	if (uri == NULL) {
		return ;
	}

	int uriLen = strlen(uri);
	char hostStr[uriLen];
	char pathStr[uriLen];
	char *hostPtr, *pathPtr, *portPtr;
	int port = 80;
	hostPtr = strstr(uri, "//");
	if (hostPtr == NULL) {
		return;
	}
	hostPtr += 2;
	pathPtr = strchr(hostPtr, '/');
	if (pathPtr == NULL) {
		int len = strlen(hostPtr);
		memcpy(hostStr, hostPtr, len);
		hostStr[len] = '\0';
		strcpy(pathStr, "/");
	} else {
		int len = strlen(hostPtr) - strlen(pathPtr);
		memcpy(hostStr, hostPtr, len);
		hostStr[len] = '\0';
		strcpy(pathStr, pathPtr);
	}
	portPtr = strchr(hostStr, ':');
	if (portPtr != NULL) {
		hostStr[strlen(hostStr) - strlen(portPtr)] = '\0';
		portPtr++;
		port = atoi(portPtr);
	}
	struct hostent* host;
	if ((host = gethostbyname(hostStr)) == NULL) {
		return ;
	}

	if (data == NULL) {
		return ;
	}

	int fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		return;
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr = *((struct in_addr*)host->h_addr);

	if (connect(fd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
		return;
	}

	if (setSocketTimeOut(fd, TIME_OUT, TIME_OUT) != 0) {
		return;
	}

	char* request = NULL;
	int requestLen = dataLen + 1024;
	request = (char*)malloc(requestLen);
	if (request == NULL) {
		return ;
	}
	memset(request, 0, requestLen);
	sprintf(request,
			"POST %s HTTP/1.1\r\n"
			"Host: %s\r\n"
	        "Accept: */*\r\n"
	        "User-Agent: %s\r\n"
			"Connection: close\r\n"
			"Content-Length: %d\r\n\r\n",
	        pathStr,
	        hostStr,
	        agent,
	        dataLen);
	requestLen = strlen(request);
	memcpy(request+requestLen, data, dataLen);
	requestLen += dataLen;
	send(fd, request, requestLen, 0);
	free(request);

	int recvTotal = 0, recvLen = 0;
	char buffer[BUFFER_SIZE];
	*response = NULL;
	while ((recvLen = recv(fd, buffer, BUFFER_SIZE, 0)) > 0) {
		if (*response == NULL) {
			recvTotal = recvLen;
			*response = (char*)malloc(recvTotal);
			if (*response == NULL) {
				break;
			}
			memcpy(*response, buffer, recvLen);
		} else {
			*response = (char*)realloc(*response, recvTotal+recvLen);
			if (*response == NULL) {
				break;
			}
			memcpy(*response + recvTotal, buffer, recvLen);
			recvTotal += recvLen;
		}
	}
	*responseLen = recvTotal;
	close(fd);
}

int setSocketTimeOut(int fd, int sendSeconds, int recvSeconds)
{
	struct timeval sendTimeVal, recvTimeVal;
	if (fd <= 0) {
		return -1;
	}

	sendTimeVal.tv_sec = sendSeconds > 0 ? sendSeconds : TIME_OUT;
	sendTimeVal.tv_usec = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &sendTimeVal, sizeof(sendTimeVal)) == -1) {
		return -2;
	}

	recvTimeVal.tv_sec = recvSeconds > 0 ? recvSeconds : TIME_OUT;
	recvTimeVal.tv_usec = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &recvTimeVal, sizeof(recvTimeVal)) == -1) {
		return -3;
	}

	return 0;
}
