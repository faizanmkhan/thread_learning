#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *choose_prime(void *arg)
{
	int index = *((int *)arg); 
	 printf("%d ", prime[index]);
	 free(arg);
	return NULL;
}
int main(void)
{
	int	i = 0;
	int *a;
	pthread_t	th[10];
	while (i < 10)
	{
		a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i], NULL, &choose_prime, a))
			perror("Failed to create thread\n");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if(pthread_join(th[i], NULL))
			perror("Failed to create join\n");
		i++;
	}
	printf("\n");
	return (0);
}
