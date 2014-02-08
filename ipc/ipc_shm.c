#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>

#define MAP_FILE_U "./map_file"
#define MAP_SIZE_U 1024

struct shm_buf_u {
	char msg[10];
};

void mmap_main()
{
	pid_t pid;
	printf("fork\n");
	pid = fork();
	if(pid > 0) {//parent
		int fd = open(MAP_FILE_U, O_RDWR | O_CREAT, 0644);
		if(fd < 0) {
			printf("parent open failed\n");
			return;
		}
		lseek(fd, MAP_SIZE_U, SEEK_SET);
		write(fd, "", 1);

		void *shmaddr = mmap(NULL, MAP_SIZE_U, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if(shmaddr == NULL) {
			printf("parent mmap failed\n");
			close(fd);
			return;
		}

		struct shm_buf_u buf;
		strcpy(buf.msg, "hello");
		memcpy(shmaddr, (void*)(&buf), sizeof(buf));
		printf("parent shm write %s\n", buf.msg);
		munmap(shmaddr, MAP_SIZE_U);

		close(fd);
		wait(NULL);
		unlink(MAP_FILE_U);
	} else if(pid == 0) {//child
		sleep(1);
		int fd = open(MAP_FILE_U, O_RDWR | O_CREAT, 0644);
		void *shmaddr = mmap(NULL, MAP_SIZE_U, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		struct shm_buf_u* bufp;
		bufp = (struct shm_buf_u*)shmaddr;
		printf("child shm read %s\n", bufp->msg);
		munmap(shmaddr, MAP_SIZE_U);
		close(fd);
	}
}

#define PATH_U "."
#define SHM_SIZE 1024

void shm_main()
{
	pid_t pid;
	printf("fork\n");
	pid = fork();
	if(pid > 0) {//parent
		key_t key;
		key = ftok(PATH_U, 'h');
		int shmid;
		shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
		if(shmid == -1) {
			printf("parent shmget failed\n");
			return;
		}

		char* msg = "hello";
		void *shmaddr = shmat(shmid, NULL, 0);
		memcpy(shmaddr, (void*)msg, strlen(msg) + 1);
		printf("parent shm write %s\n", (char*)shmaddr);

		shmdt(shmaddr);

		wait(NULL);
	} else if(pid == 0) {//child
		sleep(1);
		key_t key;
		key = ftok(PATH_U, 'h');
		int shmid;
		shmid = shmget(key, SHM_SIZE, IPC_CREAT);
		if(shmid == -1) {
			printf("child shmget failed\n");
			return;
		}

		void *shmaddr = shmat(shmid, NULL, 0);
		printf("child shm read %s\n", (char*)shmaddr);

		shmdt(shmaddr);
	}
}

int main(int argc, char* argv[])
{
//	mmap_main();
	shm_main();

	return 0;
}
