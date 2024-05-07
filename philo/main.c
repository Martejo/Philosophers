/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:54:51 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/22 15:02:38 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philos;
	t_mtx	*forks;

	if (!args_are_valid(argc, argv))
		return (EXIT_FAILURE);
	if (!allocate_struct(&table, &philos, &forks, ft_atol(argv[1])))
		return (print_error(ERR_MALLOC), EXIT_FAILURE);
	init_table(table, philos, argv);
	init_forks(forks, table->philo_nbr);
	init_philos(philos, table, forks);
	init_simulation(table, forks, philos);
	return (0);
}
