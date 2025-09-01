#include "philo.h"

bool	init_mutex(t_data *data)
{
	int	i;
	
	if (pthread_mutex_init(&data->status[0], NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->status[1], NULL) != 0)
		return (pthread_mutex_destroy(&data->status[0]), false);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->philo->meal, NULL) != 0)
			return (destroy_meal_mutex(data, i - 1), false);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_fork_mutex(data, i -1), false);
		i++;
	}
	return (true);
}

bool	start_diner(t_data *data)
{
	int	i;

	if (init_mutex(data) == false)
		return (false);
	i = 0;
	data->start_time = get_time_in_ms();
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i], NULL, &routine, &data->philo[i]) != 0)
			return (detach_threads(data, i - 1), false);
		i++;
	}
	return (true);
}

bool	end_diner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philo->meal);
		i++;
	}
	pthread_mutex_destroy(&data->status[DEAD]);
	pthread_mutex_destroy(&data->status[FULL]);
	return (true);
}
