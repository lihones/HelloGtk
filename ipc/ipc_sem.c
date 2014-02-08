#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

#define PATH_U "."

union semun_u {
	int val;			/* value for SETVAL */
	struct semid_ds *buf;	/* buffer for IPC_STAT & IPC_SET */
	unsigned short *array;	/* array for GETALL & SETALL */
	struct seminfo *__buf;	/* buffer for IPC_INFO */
	void *__pad;
};

void sem_main()
{
	pid_t pid;
	printf("fork\n");
	pid = fork();
	if(pid > 0) {//parent
		key_t key;
		key = ftok(PATH_U, 's');
		int semid;
		semid = semget(key, 1, IPC_CREAT | 0666);
		if(semid < 0) {
			printf("parent semget failed\n");
			return;
		}

		union semun_u semarg;
		semarg.val = 2;
		if(semctl(semid, 0, SETVAL, semarg) == -1) {
			printf("parent semctl setval failed\n");
		}
		printf("parent semctl set sem %d\n", semarg.val);

		struct sembuf buf;
		buf.sem_num = 0;
		buf.sem_op = -1;
		buf.sem_flg = SEM_UNDO;

		if(semop(semid, &buf, 1) == -1) {
			printf("parent semop p failed\n");
			return;
		}
		printf("parent semop p\n");

		sleep(3);

		buf.sem_num = 0;
		buf.sem_op = 1;
		buf.sem_flg = SEM_UNDO;
		if(semop(semid, &buf, 1) == -1) {
			printf("parent semop v failed\n");
			return;
		}
		printf("parent semop v\n");

		wait(NULL);

		if(semctl(semid, 0, IPC_RMID) == -1) {
			printf("parent semctl rmid failed\n");
			return;
		}
	} else if(pid == 0) {//child
		key_t key;
		key = ftok(PATH_U, 's');
		int semid;
		semid = semget(key, 1, IPC_CREAT | 0666);
		if(semid < 0) {
			printf("child semget failed\n");
			return;
		}

		sleep(1);

		struct sembuf buf;
		buf.sem_num = 0;
		buf.sem_op = -1;
		buf.sem_flg = SEM_UNDO;
		if(semop(semid, &buf, 1) == -1) {
			printf("child semop p failed\n");
			return;
		}
		printf("child semop p\n");

		sleep(1);

		buf.sem_num = 0;
		buf.sem_op = 1;
		buf.sem_flg = SEM_UNDO;
		if(semop(semid, &buf, 1) == -1) {
			printf("child semop v failed");
			return;
		}
		printf("child semop v\n");
	}
}

int main(int argc, char* argv[])
{
	sem_main();

	return 0;
}
