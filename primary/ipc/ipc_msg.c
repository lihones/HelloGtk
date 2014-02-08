#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATH_U "."

#define MSG_TYPE_TEST 5

struct msg_buf_u {
	long mtype;
	char mtext[10];
};

void msg_main()
{
	pid_t pid;
	printf("fork\n");
	pid = fork();
	if(pid > 0) {//parent
		key_t key;
		key = ftok(PATH_U, 'm');
		int msgid;
		msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
		if(msgid == -1) {
			printf("parent msgget failed\n");
			return;
		}

		struct msg_buf_u sb;
		sb.mtype = MSG_TYPE_TEST;
		strcpy(sb.mtext, "hello");
		int ret;
		ret = msgsnd(msgid, (void*)(&sb), strlen(sb.mtext), IPC_NOWAIT);
		if(ret == -1) {
			printf("parent msgsnd failed\n");
			return;
		}
		printf("parent msgsnd: %s(%d)\n", sb.mtext, sb.mtype);

		wait(NULL);

		ret = msgctl(msgid, IPC_RMID, NULL);
		if(ret == -1) {
			printf("parent msgctl IPC_RMID failed\n");
			return;
		}
	} else if(pid == 0) {//child
		key_t key;
		key = ftok(PATH_U, 'm');
		int msgid;
		msgid = msgget(key, IPC_CREAT | 0666);
		if(msgid == -1) {
			printf("child msgget failed\n");
			return;
		}

		struct msg_buf_u recv;
		int ret;
		ret = msgrcv(msgid, (void*)(&recv), 10, MSG_TYPE_TEST, IPC_NOWAIT);
		if(ret == -1) {
			printf("child msgsnd failed\n");
			return;
		}
		recv.mtext[ret] = '\0';
		printf("child msgrcv: %s\n", recv.mtext);
	}
}

int main(int argc, char* argv[])
{
	msg_main();

	return 0;
}
