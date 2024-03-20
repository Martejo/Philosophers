#include "include/philosopher.h"



int malloc_struct(t_table **table, t_philo **philos, pthread_mutex_t **forks, int phi_nbr)
{
	
}


int main(int argc, char **argv)
{
	t_table		*table;
	t_philo		*philos;
	pthread_mutex_t	*forks;

	if (!args_are_valid(argc, argv))
		return (0);
	malloc_struct(&table, &philos, &forks, ft_atol(argv[1]));
	init_launcher(table, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, table, forks, argv, ft_atol(argv[1]));
	thread_create(table, forks);
	return (0);
}