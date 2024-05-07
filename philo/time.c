/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:24:47 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/25 16:40:40 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_elapsed_time_ms(long timestamp_start)
{
	return (get_time() - timestamp_start);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(t_table *table, long ms)
{
	long	start_time;

	start_time = get_time();
	(void)table;
	while ((get_time() - start_time) < ms)
		usleep(100);
}
