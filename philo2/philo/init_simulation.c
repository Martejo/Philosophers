/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:42:28 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/20 16:18:04 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_table *table, t_mtx *forks, t_philo *philos)
{
	t_thread	observator;
	int			i;

	i = 0;
	observator.initialized = 0;
	while (i < table->philo_nbr)
	{
		if (!safe_thread_handle(&table->philos[i], CREATE))
			break ; //Voir erreur
		i++;
	}
	if (pthread_create(&observator, NULL, &monitor, table) != 0)
		break ; //gerer erreur
	
	// pthread_mutex_lock(&table->dead_lock);
	// table->thread_ready = 1;
	// table->start_time = get_time();
	// pthread_mutex_unlock(&table->dead_lock);
	set_bool(&table->dead_lock, &table->thread_ready, 1);
	set_long(&table->dead_lock, &table->start_time, get_time());


	
	pthread_join(observer, NULL);
	terminate_and_cleanup(NULL, table, forks, i);
}