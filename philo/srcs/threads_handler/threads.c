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

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(3e4);
	}
	else
	{
		if (philo->id % 2)
			think(philo, 1);
	}
}

int	get_bool(pthread_mutex_t *mtx, int *value)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	wait_all_threads(t_philo *philo)
{
	while (!get_bool(philo->dead_lock, philo->thread_ready))
		;
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;

	wait_all_threads(philo);
	de_synchronize_philos(philo);
	
	 while (!dead_loop(philo))
	{
		eat(philo);
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
	printf("%d\n", table->philos[0].num_of_philos);
	while (i < table->philos[0].num_of_philos)
	{
		pthread_create(&table->philos[i].thread, NULL, &philo_routine, &table->philos[i]);
		i++;
	}
	pthread_mutex_lock(&table->dead_lock);
	table->thread_ready = 1;
	table->start_time = get_time();
	pthread_mutex_unlock(&table->dead_lock);
	pthread_join(observer, NULL);
	terminate_and_cleanup(NULL, table, forks, i);
	return (0);
}