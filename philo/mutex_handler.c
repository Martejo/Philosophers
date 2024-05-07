/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:23:53 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/22 14:50:11 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_handle(t_mtx *mutex, t_code mtxcode)
{
	if (LOCK == mtxcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == mtxcode)
		pthread_mutex_unlock(mutex);
	else if (INIT == mtxcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == mtxcode)
		pthread_mutex_destroy(mutex);
}
