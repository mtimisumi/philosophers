#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_philo(philo);
	sleep(2);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	return (NULL);
}

bool	start_diner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i], NULL, &routine, &data->philo[i]) != 0)
			return (false);
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
		if (pthread_join(data->philos[i], NULL) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}
