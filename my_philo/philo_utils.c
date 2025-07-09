/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:22:53 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/08 21:57:57 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int i;
	int number;

	i = 1;
	while (i < argc)
	{
		if(is_digits(argv[i]))
			return (error_arg("Only positive numbers are accepted", EXIT_FAILURE));
		number = atoi_philo(argv[i]);
		if (i == 1 && (number <= 0 || number > MAX_PHILO))
			return (error_arg("Invalid number of Philosophers", EXIT_FAILURE));
		if (i != 1 && number == -1)
			return (error_arg("Number not in valid range", EXIT_FAILURE));
		i++;
	}
	return (0);
}

time_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	delay_simulation(time_t start_time)
{	
	while (get_time_ms() < start_time)
		usleep(1000);
}

static void	status_arg(t_philo *philo, char *str)
{
	printf("%ld, %d, %s\n", get_time_ms() - philo->simu->start_time,
		philo->id + 1, str);
}

void	print_status(t_philo *philo, int stop_flag, t_status status)
{
	pthread_mutex_lock(&philo->simu->print_lock);
	if (check_stop_flag(philo->simu) == 0 && stop_flag == 1)
	{
		pthread_mutex_unlock(&philo->simu->print_lock);
		return ;
	}
	if (status == HAS_DIED)
		status_arg(philo, "died");
	else if (status == IS_EATING)
		status_arg(philo, "is eating");
	else if (status == IS_SLEEPING)
		status_arg(philo, "is sleeping");
	else if (status == HAS_LEFT_FORK)
		status_arg(philo, "has taken left fork");
	else if (status == HAS_RIGHT_FORK)
		status_arg(philo, "has taken right fork");
	else if (status == IS_THINKING)
		status_arg(philo, "is thinking");
	pthread_mutex_unlock(&philo->simu->print_lock);
}
