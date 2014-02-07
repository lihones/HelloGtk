#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

void pipe_main()
{
	int fd[2];
	if(pipe(fd) < 0) {
		printf("pipe failed\n");
		return ;
	}
	printf("pipe\n");

	pid_t pid;
	printf("fork\n");
	pid = fork();
	if(pid > 0) {//parent
		close(fd[0]);
		char* msg = "hello";
		write(fd[1], msg, strlen(msg));
		printf("parent write: %s\n", msg);
		wait(NULL);
		close(fd[1]);
	} else if(pid == 0) {//child
		close(fd[1]);
		char buf[1024];
		int n;
		n = read(fd[0], buf, 1023);
		if(n > 0) {
			buf[n] = '\0';
			printf("child read: %s\n", buf);
		}
		close(fd[0]);
	}
}

#define FIFO_NAME "/tmp/ipc_pipe_named"

void pipe_named_main()
{
	pid_t pid;
	printf("fork\n");
	pid = fork();
	if(pid > 0) {//parent
		if((mkfifo(FIFO_NAME, O_CREAT | O_EXCL) < 0) && (errno != EEXIST)) {
			printf("mkfifo failed\n");
			return;
		}

		int fd;
		fd = open(FIFO_NAME, O_WRONLY | O_NONBLOCK, 0);
		if(fd < 0) {
			printf("open fifo failed(%d)\n", fd);
			return;
		}

		char* msg = "hello";
		int n;
		n = write(fd, msg, strlen(msg));
		printf("parent write %s(%d)\n", msg, n);
		close(fd);

		wait(NULL);
		unlink(FIFO_NAME);
	} else if(pid == 0) {//child
		int fd;
		fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK, 0);
		char buf[1024];
		int n;
		n = read(fd, buf, 1023);
		if(n > 0) {
			buf[n] = '\0';
			printf("child read %s\n", buf);
		}
		close(fd);
	}
}

int main(int argc, char* argv[])
{
//	pipe_main();
	pipe_named_main();

	return 0;
}
