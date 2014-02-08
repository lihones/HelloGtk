#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_u;
pthread_cond_t cond_u;

void* thread_func_a(void *arg)
{
	printf("thread_a start\n");
	pthread_mutex_lock(&mutex_u);
	printf("thread_a lock\n");
	printf("thread_a cond wait start\n");
	pthread_cond_wait(&cond_u, &mutex_u);
	printf("thread_a cond wait end\n");
	pthread_mutex_unlock(&mutex_u);
	printf("thread_a unlock\n");
	return NULL;
}

void* thread_func_b(void *arg)
{
	printf("thread_b start\n");
	pthread_mutex_lock(&mutex_u);
	printf("thread_b lock\n");
	sleep(3);
	printf("thread_b cond signal\n");
	pthread_cond_signal(&cond_u);
	pthread_mutex_unlock(&mutex_u);
	printf("thread_b unlock\n");
	return NULL;
}

void thread_cond_main()
{
	pthread_mutex_init(&mutex_u, NULL);
	pthread_cond_init(&cond_u, NULL);

	pthread_t ta;
	pthread_create(&ta, NULL, thread_func_a, NULL);
	pthread_t tb;
	pthread_create(&tb, NULL, thread_func_b, NULL);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	pthread_mutex_destroy(&mutex_u);
	pthread_cond_destroy(&cond_u);
}

int main(int argc, char* argv[])
{
	thread_cond_main();

	return 0;
}
