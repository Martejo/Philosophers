/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:31:38 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/15 09:47:22 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

// // Gets the current time in milliseconds

// long long	get_time(int time_status)
// {
// 	struct timeval	time;

// 	(void)time_status;
// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	//printf("%zu\n", (size_t)time.tv_sec * 1000 + time.tv_usec / 1000);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

long long	get_time(int time_status)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL))
		exit_error("Gettimeofday failed");
	if (MILLISECOND == time_status)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (MICROSECOND == time_status)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else if (SECONDS == time_status)
		return (time.tv_sec + time.tv_usec / 1e6);
	else
		exit_error("Wrong input to gettime:"
			"use <MILLISECOND> <MICROSECOND> <SECONDS>");
	return (0);
}

// void	precise_usleep(long usec)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = get_time(MICROSECOND);
// 	while (get_time(MICROSECOND) - start < usec)
// 	{
// 		elapsed = get_time(MICROSECOND) - start;
// 		rem = usec - elapsed;
// 		if (rem > 1e4)
// 			usleep(rem / 2);
// 		else
// 			while (get_time(MICROSECOND) - start < usec)
// 				;
// 	}
// }

// long long	time_diff(long long past, long long pres)
// {
// 	return (pres - past);
// }

// void		precise_usleep(long long time, t_philo *philo)
// {
// 	long long i;

// 	i = get_time(MILLISECOND);
// 	while (!(philo->dead))
// 	{
// 		if (time_diff(i, get_time(MILLISECOND)) >= time)
// 			break ;
// 		usleep(time / 10);
// 	}
// }

void precise_usleep(long long usec) {
    long long start, now, elapsed, remaining;

    start = get_time(MICROSECOND); // Assurez-vous que get_time retourne des microsecondes ici
    remaining = usec;

    while (remaining > 0) {
        usleep(remaining > 1000 ? remaining / 2 : remaining); // Dormez la moitié du temps restant ou tout s'il reste moins de 1 milliseconde
        now = get_time(MICROSECOND);
        elapsed = now - start;
        remaining = usec - elapsed;
    }
}


// void	precise_usleep(long long usec)
// {
// 	long long	start;
// 	start = get_time(MILLISECOND);
// 	while ((get_time(MILLISECOND) - start) < usec)
// 		usleep(usec / 10);
// }

