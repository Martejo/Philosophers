#include "include/philosopher.h"




int main(int argc, char **argv)
{
	t_table		table;
	t_philo		philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (!args_are_valid(argc, argv))
		return (0);
	init_launcher(&table, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, &table, forks, argv, ft_atol(argv[1]));
	thread_create(&table, forks);
	return (0);
}