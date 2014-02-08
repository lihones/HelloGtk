#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

void redirect_main()
{
	int stdout_u;
	stdout_u = fileno(stdout);
	char* file_path = "./text";
	int fd = open(file_path, O_RDWR | O_CREAT);
	int out_u = dup(stdout_u);
	dup2(fd, stdout_u);
	close(fd);
	printf("hello\n");
	fflush(stdout);
	dup2(out_u, stdout_u);
	printf("hello\n");
}

int main(int argc, char* argv[])
{
	redirect_main();

	return 0;
}
