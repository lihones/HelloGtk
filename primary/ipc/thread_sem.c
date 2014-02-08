#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_u;

void* thread_func_a(void *arg)
{
	printf("thread_a start\n");
	sem_wait(&sem_u);
	printf("thread_a sem wait\n");
	sleep(3);
	sem_post(&sem_u);
	printf("thread_a sem post\n");
	return NULL;
}

void* thread_func_b(void *arg)
{
	printf("thread_b start\n");
	sem_wait(&sem_u);
	printf("thread_b sem wait\n");
	sleep(3);
	sem_post(&sem_u);
	printf("thread_b sem post\n");
	return NULL;
}

void thread_sem_main()
{
	sem_init(&sem_u, 0, 1);

	pthread_t ta;
	pthread_create(&ta, NULL, thread_func_a, NULL);
	pthread_t tb;
	pthread_create(&tb, NULL, thread_func_b, NULL);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	sem_destroy(&sem_u);
}

int main(int argc, char* argv[])
{
	thread_sem_main();

	return 0;
}
