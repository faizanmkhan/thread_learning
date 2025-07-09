/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:23:19 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/09 00:41:47 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep_routine(t_simu *simu, time_t sleep_time)
{
	time_t	stop;
	
	stop = get_time_ms() + sleep_time;
	while (get_time_ms() < stop)
	{
		if(check_stop_flag(simu))
			break;
		usleep(100);
	}
}

static void	think_routine(t_philo *philo, int sys_buf)
{
	time_t	time_to_think;
	
	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->simu->time_to_die
			- (get_time_ms() - philo->last_meal)
			- philo->simu->time_to_eat) / 2;
	pthread_mutex_lock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 &&  sys_buf == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (sys_buf == 1)
		print_status(philo, 1, IS_THINKING);
	sleep_routine(philo->simu, time_to_think);
}

static void	*solo_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->fork_lock[philo->left_fork]);
	print_status(philo, 1, HAS_LEFT_FORK);
	sleep_routine(philo->simu, philo->simu->time_to_die);
	print_status(philo, 1, HAS_DIED);
	pthread_mutex_lock(&philo->simu->fork_lock[philo->left_fork]);
	return (NULL);
}

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->fork_lock[philo->left_fork]);
	print_status(philo, 1, HAS_LEFT_FORK);
	pthread_mutex_lock(&philo->simu->fork_lock[philo->right_fork]);
	print_status(philo, 1, HAS_RIGHT_FORK);
	print_status(philo, 1, IS_EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	sleep_routine(philo->simu, philo->simu->time_to_eat);
	if (check_stop_flag(philo->simu) == 1)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->meal_eaten += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	print_status(philo, 1, IS_SLEEPING);
	pthread_mutex_unlock(&philo->simu->fork_lock[philo->right_fork]);
	pthread_mutex_unlock(&philo->simu->fork_lock[philo->left_fork]);
	sleep_routine(philo->simu, philo->simu->time_to_sleep);	
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo->simu->max_meal)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->simu->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	delay_simulation(philo->simu->start_time);
	if (!philo->simu->time_to_die)
		return (NULL);
	if (philo->simu->nb_philo == 1)
		return (solo_philo(philo));
	else if (philo->id % 2)
		think_routine(philo, 0);
	while (check_stop_flag(philo->simu) == 1)
	{
		eat_sleep_routine(philo);
		think_routine(philo, 1);
	}
	return (NULL);
}
