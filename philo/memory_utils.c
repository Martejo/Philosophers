/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:58:21 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/22 14:58:51 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_table **table, t_philo **philos, t_mtx **forks)
{
	if (*forks)
		free(*forks);
	if (*table)
		free(*table);
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

bool	allocate_struct(t_table **table, t_philo **philos
	, t_mtx **forks, int phi_nbr)
{
	*table = (t_table *)ft_calloc(1, sizeof(t_table));
	if (!*table)
		return (false);
	*philos = (t_philo *)ft_calloc(phi_nbr, sizeof(t_philo));
	if (!*philos)
		return (free_data(table, philos, forks), false);
	*forks = (t_mtx *)ft_calloc(phi_nbr, sizeof(t_mtx));
	if (!*forks)
		return (free_data(table, philos, forks), false);
	return (true);
}
