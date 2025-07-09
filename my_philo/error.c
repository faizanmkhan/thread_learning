/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:07:55 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/07 13:18:44 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_arg(char *str, int exit_code)
{
	printf("ERROR: %s\n", str);
	return (exit_code);
}

void *error_init(char *str, t_simu *simu)
{
	if(simu)
		free_simulation(simu);
	error_arg(str, EXIT_FAILURE);
	return (NULL);
}

void *free_simulation(t_simu *simu)
{
	unsigned int	i;

	if (!simu)
		return (NULL);
	if (simu->fork_lock)
		free(simu->fork_lock);
	if (simu->philos)
	{
		i = 0;
		while (i < simu->nb_philo)
		{
			if (simu->philos[i])
				free(simu->philos[i]);
			i++;
		}
		free (simu->philos);
	}
	free (simu);
	return (NULL);
}

int	error_init_mutex(char *str, t_simu *simu)
{
	if (simu)
		free_simulation(simu);
	return (error_arg(str, EXIT_FAILURE));
}