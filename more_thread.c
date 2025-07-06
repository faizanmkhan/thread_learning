#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_fuel;
int fuel = 0;

void *fuel_filling(void *arg)
{
	printf("filling fuel\n");
	return (NULL);
}

void *car(void *arg)
{
	printf("waiting for fuelling\n");
	return (NULL);
}

int main(void)
{
	pthread_t	th[2];
	int i;

	pthread_mutex_init(&mutex_fuel, NULL);
	i = 0;
	while (i < 2)
	{
		if (i == 1)
		{
			if(pthread_create(&th[i], NULL, &fuel_filling, NULL))
				perror("Fail to create thread\n");
		}
		else
		{
			if(pthread_create(&th[i], NULL, &car, NULL))
				perror("Failed to create thread\n");
		}
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if(pthread_join(th[i], NULL))
			perror("Failed to join theread\n");
		i++;
	}
	pthread_mutex_destroy(&mutex_fuel);
	return (0);
}