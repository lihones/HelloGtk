#ifndef __HTTPCLIENT_H__
#define __HTTPCLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

void httpGet(char* uri, char** response, unsigned int* responseLen);
void httpPost(char* uri, char* data, unsigned int dataLen,
			  char** response, unsigned int* responseLen, char* agent);

#ifdef __cplusplus
}
#endif

#endif
