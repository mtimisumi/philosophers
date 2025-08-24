#include "philo.h"

bool	start_diner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_mutexes(data, i - 1);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i], NULL, &routine, &data->philo[i]) != 0)
		{
			detach_threads(data, i - 1);
			return (false);
		}
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
	return (true);
}
