/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:01 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/20 16:04:19 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	handle_thread_error(int status, t_code trdcode)
{
	if (0 == status)
		return (true);
	if (EAGAIN == status)
		return (print_error(CREATE_EAGAIN), false);
	else if (EPERM == status)
		return (print_error(CREATE_EPERM), false);
	else if (EINVAL == status && CREATE == trdcode)
		return (print_error(CREATE_EINVAL), false);
	else if (EINVAL == status && (JOIN == trdcode || DETACH == trdcode))
		return (print_error(JOIN_EINVAL), false);
	else if (ESRCH == status)
		return (print_error(JOIN_ESRCH), false);
	else if (EDEADLK == status)
		return (print_error(JOIN_EDEADLK), false);
	return (true);
}

bool	safe_thread_handle(t_philo *philo, t_code code)
{
	if (CREATE == code)
	{
		if (!handle_thread_error(pthread_create(&(philo->thread), NULL, dinner_loop, philo), code))
			return (false);
		philo->thread.initialized = 1;
	}
	else if (JOIN == code)
		return (handle_thread_error(pthread_join(philo->thread.thread, NULL), code));
	else if (DETACH == code)
		return (handle_thread_error(pthread_detach(philo->thread.thread), code));
	return (true);
}