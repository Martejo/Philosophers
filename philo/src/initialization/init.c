#include "../../include/philosopher.h"

void	init_philos(t_philo *philos, t_table *table, pthread_mutex_t *forks, char **argv, int philo_nbr)
{
	int	i;

	i = 0;
	while (i < philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].start_time = 0; // A voir
		philos[i].last_meal = 0; // A voir
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].dead = &table->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];

	}
	
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		handle_mutex_error(pthread_mutex_init(&forks[i], NULL), INIT);
		i++;
	}
}

void	init_launcher(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos	= philos;
	handle_mutex_error(pthread_mutex_init(&table->write_lock, NULL), INIT);
	handle_mutex_error(pthread_mutex_init(&table->dead_lock, NULL), INIT);
	handle_mutex_error(pthread_mutex_init(&table->meal_lock, NULL), INIT);
}