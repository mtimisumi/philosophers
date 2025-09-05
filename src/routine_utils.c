#include "philo.h"

bool	single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo->data, philo->id, FORK);
	ft_usleep(philo->data, philo->data->time_to_die);
	pthread_mutex_unlock(philo->right_fork);
	return (false);
}

int	lock_meal(t_philo *philo)
{
	int	exitcode;

	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_cur_time(philo->data->start_time);
	print_action(philo->data, philo->id, EAT);
	pthread_mutex_unlock(&philo->meal);
	exitcode = ft_usleep(philo->data, philo->data->time_to_eat);
	return (exitcode);
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

bool	think_more(t_data *data)
{
	long	stagger_time;
	long	wait_time;

	if (data->time_to_sleep == data->time_to_eat)
	{
		stagger_time = get_stagger_time(data);
		return (ft_usleep(data, stagger_time));
	}
	else if (data->time_to_sleep < data->time_to_eat)
	{
		wait_time = data->time_to_eat - data->time_to_sleep;
		stagger_time = get_stagger_time(data);
		return (ft_usleep(data, wait_time + stagger_time));
	}
	return (true);
}
