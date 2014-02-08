#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

int do_exit = 0;

void handle_signal_alarm(int sig)
{
	printf("receive SIGALRM\n");
	do_exit = 1;
}

void signal_main()
{
	signal(SIGALRM, handle_signal_alarm);
	alarm(3);
	while(!do_exit);
}

int main(int argc, char* argv[])
{
	signal_main();

	return 0;
}
