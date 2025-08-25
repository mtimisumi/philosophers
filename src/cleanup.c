#include "philo.h"

void	destroy_mutexes(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	free(data->forks);
	data->forks = NULL;
}

void	detach_threads(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_detach(data->philos[i]);
		i--;
	}
	free(data->philos);
	data->philos = NULL;
}

void	destroy_philo(t_data *data, int i)
{
	while (i >= 0)
	{
		if (data->philo[i].meal)
		{
			pthread_mutex_destroy(data->philo[i].meal);
			free(data->philo[i].meal);
		}
		i--;
	}
	free(data->philo);
}

void	cleanup(t_data *data)
{
	if (data->status)
	{
		pthread_mutex_destroy(&data->status[0]);
		pthread_mutex_destroy(&data->status[1]);
		free(data->status);
	}
	if (data->philos)
		detach_threads(data, data->philo_count - 1);
	if (data->forks)
		destroy_mutexes(data, data->philo_count - 1);
	if (data->philo)
		destroy_philo(data, data->philo_count - 1);
}
