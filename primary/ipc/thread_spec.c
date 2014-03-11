#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

pthread_key_t key;

void print_ids(char *who)
{
	printf("%s: pid-%x, tid-%x, ptid-%x\n", who, getpid(), (long int)syscall(__NR_gettid), pthread_self());
}

void* thread_func_a(void *arg)
{
	print_ids("thread_a");
	int tid = pthread_self();
	pthread_setspecific(key, (void*)(&tid));
	sleep(1);
	int *spec = (int*)(pthread_getspecific(key));
	printf("thread_a get spec: %x\n", *spec);
	sleep(10);
	return NULL;
}

void* thread_func_b(void *arg)
{
	print_ids("thread_b");
	int tid = pthread_self();
	pthread_setspecific(key, (void*)(&tid));
	int *spec = (int*)(pthread_getspecific(key));
	printf("thread_b get spec: %x\n", *spec);
	sleep(10);
	return NULL;
}

void thread_mutex_main()
{
	print_ids("main thread");

	pthread_key_create(&key, NULL);

	pthread_t ta;
	pthread_create(&ta, NULL, thread_func_a, NULL);
	pthread_t tb;
	pthread_create(&tb, NULL, thread_func_b, NULL);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	pthread_key_delete(key);
}

int main(int argc, char* argv[])
{
	thread_mutex_main();

	return 0;
}
