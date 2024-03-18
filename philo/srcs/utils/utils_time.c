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

long long	get_time(int time_status)
{
	struct timeval	time;

	(void)time_status;
	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// long long	get_time(int time_status)
// {
// 	struct timeval	time;
// 	long long times;
	
// 	if (gettimeofday(&time, NULL))
// 		exit_error("Gettimeofday failed");
// 	if (MILLISECOND == time_status)
// 	{
// 		times = time.tv_sec * 1e3 + time.tv_usec / 1e3;
// 		return (times);
// 	}
// 	else if (MICROSECOND == time_status)
// 		return (time.tv_sec * 1e6 + time.tv_usec);
// 	else if (SECONDS == time_status)
// 		return (time.tv_sec + time.tv_usec / 1e6);
// 	else
// 		exit_error("Wrong input to gettime:"
// 			"use <MILLISECOND> <MICROSECOND> <SECONDS>");
// 	return (0);
// }

// void	precise_usleep(long long usec)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = get_time(MILLISECOND);
// 	while (get_time(MILLISECOND) - start < usec)
// 	{
// 		elapsed = get_time(MILLISECOND) - start;
// 		rem = usec - elapsed;
// 		if (rem > 1e4)
// 			usleep(rem / 2);
// 		else
// 			while (get_time(MILLISECOND) - start < usec)
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

// void precise_usleep(long long usec) {
//     long long start, now, elapsed, remaining;

//     start = get_time(MILLISECOND); // Assurez-vous que get_time retourne des microsecondes ici
//     remaining = usec;

//     while (remaining > 0) {
//         usleep(remaining > 1000 ? remaining / 2 : remaining); // Dormez la moitié du temps restant ou tout s'il reste moins de 1 milliseconde
//         now = get_time(MILLISECOND);
//         elapsed = now - start;
//         remaining = usec - elapsed;
//     }
// }

// long long get_time_microseconds() {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);
//     return tv.tv_sec * 1000000LL + tv.tv_usec;
// }

// void precise_usleep(long long usec) {
//     long long start_time = get_time_microseconds();
//     long long end_time = start_time + usec;
//     long long current_time;

//     // Ajustez dynamiquement la marge en fonction de la durée de l'attente.
//     long long margin = usec > 5000 ? 200 : 50; // Exemple d'ajustement dynamique.

//     if (usec > margin) {
//         usleep(usec - margin); // Utilisez une marge ajustée.
//     }

//     // Optimisation de la boucle de vérification active pour minimiser l'utilisation du CPU.
//     do {
//         current_time = get_time_microseconds();
//         if (end_time - current_time > 1000) {
//             // Si le temps restant est suffisamment long, reposez brièvement pour réduire l'utilisation du CPU.
//             usleep(100); // Ajustez cette valeur selon les besoins.
//         }
//     } while (current_time < end_time);
// }


void	precise_usleep(long long usec)
{
	long long	start;
	start = get_time(MILLISECOND);
	while ((get_time(MILLISECOND) - start) < usec)
	{
		usleep(150);
	}
}

