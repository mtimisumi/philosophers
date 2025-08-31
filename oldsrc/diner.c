// #include "philo.h"

// bool	init_other_mutex(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while ( i < data->philo_count)
// 	{
// 		if (pthread_mutex_init(data->philo->meal, NULL) != 0)
// 			return (destroy_mutexes(data->philo->meal, i), false);
// 		i++;
// 	}
// 	if (pthread_mutex_init(data->status, NULL) != 0)
// 		return (false);
// 	if (pthread_mutex_init(&data->status[1], NULL) != 0)
// 		return (destroy_mutexes(data->status, 0), false);
// 	return (true);
// }

// bool	start_diner(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philo_count)
// 	{
// 		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
// 		{
// 			destroy_mutexes(data->forks, i - 1);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	init_other_mutex(data);
// 	while (i < data->philo_count)
// 	{
// 		if (pthread_create(&data->philos[i], NULL, &routine, &data->philo[i]) != 0)
// 		{
// 			detach_threads(data->philos, i - 1);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// bool	end_diner(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philo_count)
// 	{
// 		pthread_join(data->philos[i], NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->philo_count)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		i++;
// 	}
// 	return (true);
// }


#include "philo.h"

bool	init_other_mutex(t_data *data)
{
	int	i;

	i = 0;
	// Fix: Initialize each philosopher's meal mutex correctly
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(data->philo[i].meal, NULL) != 0)
		{
			// Clean up previously initialized meal mutexes
			while (--i >= 0)
				pthread_mutex_destroy(data->philo[i].meal);
			return (false);
		}
		i++;
	}
	
	// Initialize status mutexes
	if (pthread_mutex_init(&data->status[0], NULL) != 0)
	{
		// Clean up meal mutexes if status mutex fails
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(data->philo[i].meal);
			i++;
		}
		return (false);
	}
	if (pthread_mutex_init(&data->status[1], NULL) != 0)
	{
		pthread_mutex_destroy(&data->status[0]);
		// Clean up meal mutexes if second status mutex fails
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(data->philo[i].meal);
			i++;
		}
		return (false);
	}
	return (true);
}

bool	start_diner(t_data *data)
{
	int	i;

	i = 0;
	// Initialize fork mutexes
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_mutexes(data->forks, i - 1);
			return (false);
		}
		i++;
	}
	
	// Initialize other mutexes (meal and status)
	if (!init_other_mutex(data))
	{
		destroy_mutexes(data->forks, data->philo_count - 1);
		return (false);
	}
	
	i = 0;
	// Create philosopher threads
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i], NULL, &routine, &data->philo[i]) != 0)
		{
			detach_threads(data->philos, i - 1);
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
	
	// Clean up all mutexes
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(data->philo[i].meal);
		i++;
	}
	
	pthread_mutex_destroy(&data->status[0]);
	pthread_mutex_destroy(&data->status[1]);
	
	return (true);
}