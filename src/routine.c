#include "philo.h"

int	lock_meal(t_philo *philo)
{
	int	exitcode;

	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_cur_time(philo->data->start_time);
	pthread_mutex_unlock(&philo->meal);
	print_action(philo->data, philo->id, EAT);
	exitcode = ft_usleep(philo->data, philo->data->time_to_eat);
	return (exitcode);
}

bool	eat_meal(t_philo *philo)
{
	int	exitcode;

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

bool	philo_is_full(t_philo *philo)
{
	if (philo->data->amount_of_meals == -1)
		return (false);
	if (philo->meal_count < philo->data->amount_of_meals)
		return (false);
	pthread_mutex_lock(&philo->data->lock[FULL]);
	philo->data->full++;
	pthread_mutex_unlock(&philo->data->lock[FULL]);
	return (true);
}

long	get_stagger_time(t_data *data)
{
	long	max_stagger_time;
	long	wait_time;
	long	stagger_time;

	wait_time = data->time_to_eat + data->time_to_sleep;
	max_stagger_time = data->time_to_die - wait_time;
	if (max_stagger_time <= 10)
	{
		stagger_time = max_stagger_time / 3;
		if (stagger_time == 0)
			stagger_time = 1;
		return (stagger_time);
	}
	else
	{
		stagger_time = max_stagger_time / 7;
		if (stagger_time == 0)
		stagger_time = 1;
		return (stagger_time);
	}
}

bool	think(t_philo *philo, t_data *data)
{
	long	stagger_time;
	long	wait_time;

	print_action(philo->data, philo->id, THINK);
	if (philo->data->philo_count % 2 != 0)
	{
		if (data->time_to_sleep > data->time_to_eat)
			return (true);
		if (data->time_to_sleep == data->time_to_eat)
		{
			stagger_time = get_stagger_time(data);
			if (ft_usleep(data, stagger_time) == false)
				return (false);
		}
		if (data->time_to_sleep < data->time_to_eat)
		{
			wait_time = data->time_to_eat - data->time_to_sleep;
			stagger_time = get_stagger_time(data);
			if (ft_usleep(data, wait_time + stagger_time) == false)
				return (false);
		}
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
		if (think(philo, philo->data) == false)
			break ;
	}
	return (NULL);
}
