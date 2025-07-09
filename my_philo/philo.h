/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:13:46 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/09 00:41:13 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILO 200

typedef struct s_philo t_philo;

typedef struct s_simu
{
	unsigned int	nb_philo;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				max_meal;
	int				stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*fork_lock;
	pthread_t		arbitrator;
	t_philo			**philos;
}	t_simu;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned int	meal_eaten;
	pthread_mutex_t	meal_time_lock;
	time_t			last_meal;
	struct s_simu	*simu;
}	t_philo;

typedef enum e_status
{
	HAS_DIED,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	HAS_LEFT_FORK,
	HAS_RIGHT_FORK,
}	t_status;

int	error_arg(char *str, int exit_code);
int	atoi_philo(char *str);
int	is_digits(char *str);
int	check_args(int argc, char **argv);
void *free_simulation(t_simu *simu);
void *error_init(char *str, t_simu *simu);
int	error_init_mutex(char *str, t_simu *simu);
void *free_simulation(t_simu *simu);
t_simu	*init_simulation(int argc, char **argv);
time_t	get_time_ms(void);
void	delay_simulation(time_t start_time);
int	check_stop_flag(t_simu *simu);
void	print_status(t_philo *philo, int stop_flag, t_status status);
void	*philo_routine(void *arg);
void	*arbitrator(void *arg);
void	destroy_mutexes(t_simu *simu);
void clean_simulation(t_simu *simu);
void	wait_simulation(t_simu *simu);
int start_simulation(t_simu *simu);
#endif
