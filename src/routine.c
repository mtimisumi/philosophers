#include "philo.h"

void	print_msg(char *msg, long start_time, int id)
{
	printf("%-6ld %-3d %s\n", get_cur_time(start_time), id, msg);
}

void	eat_meal(t_philo *philo)
{
	if (philo->left_fork > philo->right_fork)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_msg("has taken a fork", philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_msg("has taken a fork", philo->data->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_msg("has taken a fork", philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_msg("has taken a fork", philo->data->start_time, philo->id);
	}
		print_msg("is eating", philo->data->start_time, philo->id);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	go_sleep(t_philo *philo)
{
	print_msg("is sleeping", philo->data->start_time, philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	eat_meal(philo);
	go_sleep(philo);
	print_msg("is thinking", philo->data->start_time, philo->id);
	return (NULL);
}
