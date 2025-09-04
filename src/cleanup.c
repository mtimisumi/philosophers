#include "philo.h"

void	destroy_fork_mutex(t_data *data, int i)
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

void	destroy_meal_mutex(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->philo->meal);
		i--;
	}
	free(data->philo);
	data->philo = NULL;
}

void	destroy_lock_mutex(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->lock[i]);
		i--;
	}
}

void	cleanup(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
}
