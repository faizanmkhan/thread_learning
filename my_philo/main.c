/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:04:44 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/09 00:32:01 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_simu	*simu;
	
	(void)simu;
	if (argc < 5 || argc > 6)
		return (error_arg("Invalid number of arguments", EXIT_FAILURE));
	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	simu = init_simulation(argc, argv);
	if (!simu)
		return (EXIT_FAILURE);
	if (start_simulation(simu))// need to code
		return (EXIT_FAILURE);
	wait_simulation(simu);// need to code
	clean_simulation(simu);//need to code
}
