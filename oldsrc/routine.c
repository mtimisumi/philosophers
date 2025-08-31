#include "philo.h"

int	lock_meal(t_philo *philo)
{
	int	exitcode;

	pthread_mutex_lock(philo->meal);
	philo->last_meal = get_cur_time(philo->data->start_time);
	pthread_mutex_unlock(philo->meal);
	print_msg(philo->data, "is eating", philo->data->start_time, philo->id);
	exitcode = ft_usleep(philo->data, philo->data->time_to_eat);
	return (exitcode);
}

// bool	eat_meal(t_philo *philo)
// {
// 	int	exitcode;

// 	if (philo->left_fork > philo->right_fork)
// 	{
// 		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
// 		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
// 		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
// 		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
// 		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
// 		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
// 		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
// 	}
// 	pthread_mutex_lock(philo->meal);
// 	philo->last_meal = get_cur_time(philo->data->start_time);
// 	pthread_mutex_unlock(philo->meal);
// 	print_msg(philo->data, "is eating", philo->data->start_time, philo->id);
// 	exitcode = ft_usleep(philo->data, philo->data->time_to_eat);
// 	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
// 	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
// 	usleep(1);

// 	return (exitcode);
// }

bool	eat_meal(t_philo *philo)
{
	int	exitcode;
	// if philo is even
	if (philo->id %2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
		exitcode = lock_meal(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_msg(philo->data, "has taken a fork", philo->data->start_time, philo->id);
		exitcode = lock_meal(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
	return (exitcode);
}

bool	go_sleep(t_philo *philo)
{
	print_msg(philo->data, "is sleeping", philo->data->start_time, philo->id);
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
	pthread_mutex_lock(&philo->data->status[1]);
	philo->data->full++;
	pthread_mutex_unlock(&philo->data->status[1]);
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
		if (go_sleep(philo) == false)
			break ;
		print_msg(philo->data, "is thinking", philo->data->start_time, philo->id);
	}
	return (NULL);
}

// void	*routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->data->philo_count % 2 == 0)
// 		even_rountine();
// 	else
// 		odd_routine();
// 	while (check_dead_status(philo->data) == false)
// 	{
// 		if (eat_meal(philo) == false)
// 			break ;
// 		philo->meal_count++;
// 		if (philo_is_full(philo) == true)
// 			break ;
// 		if (go_sleep(philo) == false)
// 			break ;
// 		print_msg(philo->data, "is thinking", philo->data->start_time, philo->id);
// 	}
// 	return (NULL);
// }
