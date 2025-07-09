/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:07:36 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/08 22:25:23 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	distribute_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		if (philo->id + 1 == philo->simu->nb_philo)
			philo->left_fork = 0;
		else
			philo->left_fork = philo->id + 1;
		philo->right_fork = philo->id;
	}
	else
	{
		philo->left_fork = philo->id;
		if (philo->id + 1 == philo->simu->nb_philo)
			philo->right_fork = 0;
		else
			philo->right_fork = philo->id + 1;
	}
}

static pthread_mutex_t *init_forks(t_simu *simu)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * simu->nb_philo);
	if (!forks)
		return(error_init("Unable to initialized forks", NULL));
	i = 0;
	while (i < simu->nb_philo)
	{
		if (pthread_mutex_init(forks + i, NULL))
			return(error_init("Unable to create forks mutex", NULL));
		i++;
	}
	return (forks);
}

static int init_mutexes(t_simu *simu)
{
	simu->fork_lock = init_forks(simu);
	if (!simu->fork_lock)
		return (1);
	if (pthread_mutex_init(&simu->stop_lock, NULL))
		return (error_init_mutex("stop_lock mutex unsuccessful", simu));
	if (pthread_mutex_init(&simu->print_lock, NULL))
		return (error_init_mutex("print_lock mutex unsuccessful", simu));
	return (0);
}

static t_philo	**init_philosophers(t_simu *simu)
{
	t_philo	**philo;
	unsigned int i;
	
	i = 0;
	philo = malloc(sizeof(t_philo) * simu->nb_philo);
	if (!philo)
		return (error_init("Unable to create philosopher array", NULL));
	while (i < simu->nb_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (error_init("Unable to create philosopher", NULL));
		if (pthread_mutex_init(&philo[i]->meal_time_lock, NULL)) // need to understand
			return (error_init("Unable to create mutex", NULL));
		philo[i]->id = i;
		philo[i]->simu = simu;
		philo[i]->meal_eaten = 0;
		distribute_forks(philo[i]);
		i++;
	}
	return (philo);
}

t_simu	*init_simulation(int argc, char **argv)
{
	t_simu	*simu;
	
	simu = malloc(sizeof(t_simu));
	if (!simu)
		return (error_init("Unable to create simulation", NULL));
	simu->nb_philo = atoi_philo(argv[1]);
	simu->time_to_die = atoi_philo(argv[2]);
	simu->time_to_eat = atoi_philo(argv[3]);
	simu->time_to_sleep = atoi_philo(argv[4]);
	simu->max_meal = -1;
	if (argc == 6)
		simu->max_meal = atoi_philo(argv[5]);
	simu->philos = init_philosophers(simu);
	if (!simu->philos)
		return (NULL);
	if (!init_mutexes(simu))
		return (NULL);
	simu->stop = 1; // initialized to false
	return (simu);
}
