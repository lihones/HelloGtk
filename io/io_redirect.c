#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define STDOUT_U 1

void redirect_main()
{
	char* file_path = "./text";
	int fd = open(file_path, O_RDWR | O_CREAT);
	int out_u = dup(STDOUT_U);
	dup2(fd, STDOUT_U);
	close(fd);
	printf("hello\n");
	fflush(stdout);
	dup2(out_u, STDOUT_U);
	printf("hello\n");
}

int main(int argc, char* argv[])
{
	redirect_main();

	return 0;
}
