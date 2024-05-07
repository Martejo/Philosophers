/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:01 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 16:34:15 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_handle(t_philo *philo, t_code code)
{
	if (CREATE == code)
		pthread_create(&(philo->thread), NULL, &diner_loop, philo);
	else if (LONE_PHILO == code)
		pthread_create(&(philo->thread), NULL, &lone_philo, philo);
	else if (JOIN == code)
		pthread_join(philo->thread, NULL);
	else if (DETACH == code)
		pthread_detach(philo->thread);
}

void	wait_all_threads(t_table *table)
{
	while (!get_mtxbool(&table->mtx_table, &table->thread_ready))
		;
}
