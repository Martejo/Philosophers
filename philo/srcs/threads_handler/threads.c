#include "../../include/philosopher.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}


void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!dead_loop(philo))
	{
		if (*philo->error == 1)
			break ;
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}


uint8_t	thread_create(t_table *table, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;
	
	i = 0;
	if (pthread_create(&observer, NULL, &monitor, table->philos) != 0)
		terminate_and_cleanup("Thread creation error\n", table, forks, 0);
	while (i < table->philos[0].num_of_philos)
	{
		
		pthread_create(&table->philos[i].thread, NULL, &philo_routine, &table->philos[i]);
		i++;
	}
	pthread_join(observer, NULL);
	terminate_and_cleanup(NULL, table, forks, i);
	return (0);
}