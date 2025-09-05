#include "philo.h"

bool	eat_meal(t_philo *philo)
{
	int	exitcode;

	if (philo->data->philo_count == 1)
		return (single_philo(philo));
	if (philo->id %2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->data, philo->id, FORK);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo->data, philo->id, FORK);
		exitcode = lock_meal(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo->data, philo->id, FORK);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->data, philo->id, FORK);
		exitcode = lock_meal(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (exitcode);
}

bool	ft_sleep(t_philo *philo)
{
	print_action(philo->data, philo->id, SLEEP);
	if (ft_usleep(philo->data, philo->data->time_to_sleep) == false)
		return (false);
	return (true);
}

bool	think(t_philo *philo)
{
	print_action(philo->data, philo->id, THINK);
	if (philo->data->philo_count % 2 != 0)
	{
		if (think_more(philo->data) == false)
			return (false);
		return (true);
	}
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_dead_status(philo->data) == false)
	{
		if (eat_meal(philo) == false)
			break ;
		philo->meal_count++;
		if (philo_is_full(philo) == true)
			break ;
		if (ft_sleep(philo) == false)
			break ;
		if (think(philo) == false)
			break ;
	}
	return (NULL);
}
