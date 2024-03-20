/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:54:51 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/20 15:40:13 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_table **table, t_philo **philos, t_mtx **forks)
{
	int	i;

	i = 0;
	if (*table)
	{
		safe_mutex_handle(&(*table)->dead_lock, DESTROY);
		safe_mutex_handle(&(*table)->write_lock, DESTROY);
		free(*table);
	}
	if (*forks)
	{
		while (i < (*table)->philo_nbr)
		{
			safe_mutex_handle(&(*forks)->mutex, DESTROY);
			i++;
		}
		free(*forks);
	}
	if (*philos)
		free(*philos);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && nmemb > (size_t)(-1) / size)
	{
		return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	return ((void *)memset(ptr, 0, nmemb * size));
}

bool	allocate_struct(t_table **table, t_philo **philos, t_mtx **forks, int phi_nbr)
{
	*table = (t_table *)ft_calloc(1, sizeof(t_table));
	if (!*table)
		return (false);
	*philos = (t_philo *)ft_calloc(phi_nbr,  sizeof(t_philo));
	if (!*philos)
		return (free_data(table, philos, forks), false);
	*forks = (pthread_mutex_t *)ft_calloc(phi_nbr, sizeof(pthread_mutex_t));
	if (!*forks)
		return (free_data(table, philos, forks), false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philos;
	t_mtx	*forks;

	if (!args_are_valid(argc, argv))
		return (EXIT_FAILURE);
	if (!allocate_struct(&table, &philos, &forks, ft_atol(argv[1])))
		return (print_error(ERR_MALLOC), EXIT_FAILURE);
	if (!init_table(table, philos, ft_atol(argv[1])))
		return (free_data(&table, &philos, &forks), EXIT_FAILURE);
	if (!init_forks(forks, table->philo_nbr))
		return (free_data(&table, &philos, &forks), EXIT_FAILURE);
	init_philos(philos, table, forks);
}