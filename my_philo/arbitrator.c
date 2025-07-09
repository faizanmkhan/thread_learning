/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:02:51 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/09 00:25:39 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_stop_flag(t_simu *simu, int state)
{
	pthread_mutex_lock(&simu->stop_lock);
	simu->stop = state;
	pthread_mutex_unlock(&simu->stop_lock);
}

static int	check_philo_died(t_philo *philo)
{
	time_t	time;
	
	time = get_time_ms();
	if (time - philo->last_meal >= philo->simu->time_to_die)
	{
		set_stop_flag(philo->simu, 0);
		print_status(philo, 0, HAS_DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (0);
	}
	return (1);
}

int	check_stop_flag(t_simu *simu)
{
	int	flag;

	pthread_mutex_lock(&simu->stop_lock);
	if (simu->stop == 0)
		flag = 0; // returning true
	else
		flag = 1; // returning false
	pthread_mutex_unlock(&simu->stop_lock);
	return (flag);
}

static int	check_simulation_end(t_simu *simu)
{
	unsigned int	i;
	int		max_limit;
	
	max_limit = 0;
	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_mutex_lock(&simu->philos[i]->meal_time_lock);
		if (check_philo_died(simu->philos[i]))
			return (0);
		if (simu->max_meal != -1)
			if (simu->philos[i]->meal_eaten < (unsigned int)simu->max_meal)
				max_limit = 1;
		pthread_mutex_unlock(&simu->philos[i]->meal_time_lock);
		i++;
	}
	if (simu->max_meal != -1 && max_limit == 0)
	{
		set_stop_flag(simu, 0);
		return (0);
	}
	return (1);
}

void *arbitrator(void *arg)
{
	t_simu	*simu;
	
	simu = (t_simu *)arg;
	if (!simu->max_meal)
		return (NULL);
	set_stop_flag(simu, 1);
	delay_simulation(simu->start_time);
	while (42)
	{
		if(check_simulation_end(simu) == 0) // need to code
			return (NULL);
		usleep(1e3);
	}
	return (NULL);
}

