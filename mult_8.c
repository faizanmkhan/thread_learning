// video number 8 redo it here
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *choose_prime(void *arg)
{
	int index = *((int *)arg); 
	int sum = 0;
	int j = 0;
	while(j < 5)
	{
		sum += prime[index + j];
		j++;
	}
	printf("thread sum: %d\n", sum);
	*(int*)arg = sum;
	return (arg);
}

int main(void)
{
	int	i = 0;
	int *a;
	int *r;
	int totalSum = 0;
	pthread_t	th[2];
	while (i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if(pthread_create(&th[i], NULL, &choose_prime, a))
			perror("Failed to create thread\n");
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if(pthread_join(th[i], (void**)&r))
			perror("Failed to create join\n");
		i++;
		totalSum += *r;
		free (r);
	}

	printf("total sum : %d\n", totalSum);
	return (0);
}
