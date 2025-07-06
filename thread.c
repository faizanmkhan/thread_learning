#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine(void *arg)
{
	int num = *((int *) arg);
	printf("my thread rroutine %d function\n", num);
	usleep(250000);
	printf("ending\n");
	return (NULL);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t t1, t2;
	int num_thread;
	num_thread = 20;
	if(pthread_create(&t1, NULL, routine, (void *) &num_thread) != 0)
	{
		printf("error occur\n");
	}
	if(pthread_create(&t2, NULL, routine, (void *) &num_thread) != 0)
	{
		printf("error occur\n");
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}