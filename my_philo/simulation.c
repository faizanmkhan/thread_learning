/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:47:24 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/09 00:42:40 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_simulation(t_simu *simu)
{
	unsigned int	i;
	
	simu->start_time = get_time_ms() + (simu->nb_philo * 2 * 5);
	i = 0;
	while(i < simu->nb_philo)
	{
		if (pthread_create(&simu->philos[i]->thread, NULL,
				&philo_routine, simu->philos[i]))
			return(error_init_mutex("Philo thread unsuccessful", simu));
		i++;
	}
	if (simu->nb_philo > 1)
	{
		if (pthread_create(&simu->arbitrator, NULL, &arbitrator, simu))
			return(error_init_mutex("Arbitrator thread unsuccessful", simu));
	}
	return (0);
}

void	wait_simulation(t_simu *simu)
{
	unsigned int	i;

	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_join(simu->philos[i]->thread, NULL);
		i++;
	}
	if (simu->nb_philo > 1)
		pthread_join(simu->arbitrator, NULL);
}

void clean_simulation(t_simu *simu)
{
	destroy_mutexes(simu); 
	free_simulation(simu);
}

void	destroy_mutexes(t_simu *simu)
{
	unsigned int	i;
	
	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_mutex_destroy(&simu->fork_lock[i]);
		pthread_mutex_destroy(&simu->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&simu->print_lock);
	pthread_mutex_destroy(&simu->stop_lock);
}
