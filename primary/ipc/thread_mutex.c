#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_u;

void* thread_func_a(void *arg)
{
	printf("thread_a start\n");
	pthread_mutex_lock(&mutex_u);
	printf("thread_a lock\n");
	sleep(3);
	pthread_mutex_unlock(&mutex_u);
	printf("thread_a unlock\n");
	return NULL;
}

void* thread_func_b(void *arg)
{
	printf("thread_b start\n");
	pthread_mutex_lock(&mutex_u);
	printf("thread_b lock\n");
	sleep(1);
	pthread_mutex_unlock(&mutex_u);
	printf("thread_b unlock\n");
	return NULL;
}

void thread_mutex_main()
{
	pthread_mutex_init(&mutex_u, NULL);

	pthread_t ta;
	pthread_create(&ta, NULL, thread_func_a, NULL);
	pthread_t tb;
	pthread_create(&tb, NULL, thread_func_b, NULL);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	pthread_mutex_destroy(&mutex_u);
}

int main(int argc, char* argv[])
{
	thread_mutex_main();

	return 0;
}
