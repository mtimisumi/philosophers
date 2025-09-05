#include "philo.h"

bool	init_philo(t_data *data, int i, mutex_t *left_fork, mutex_t *right_fork)
{
	memset(&data->philo[i], 0, sizeof(t_philo));
	data->philo[i].id = i;
	data->philo[i].left_fork = left_fork;
	data->philo[i].right_fork = right_fork;
	data->philo[i].last_meal = data->start_time;
	data->philo[i].data = data;
	return (true);
}

bool	create_philos(t_data *data)
{
	int		i;
	mutex_t	*left_fork;
	mutex_t	*right_fork;

	data->philo = malloc(data->philo_count *sizeof(t_philo));
	if (!data->philo)
		return (false);
	left_fork = &data->forks[data->philo_count - 1];
	i = 0;
	while (i < data->philo_count)
	{
		right_fork = &data->forks[i];
		init_philo(data, i, left_fork, right_fork);
		left_fork = right_fork;
		i++;
	}
	return (true);
}

bool	init_data(t_data *data, char **argv)
{
	if (are_valid_args(argv) == false)
		return (false);

	memset(data, 0, sizeof(t_data));
	data->philo_count = to_pos_int(argv[1]);
	data->time_to_die = to_pos_int(argv[2]);
	data->time_to_eat = to_pos_int(argv[3]);
	data->time_to_sleep = to_pos_int(argv[4]);
	data->amount_of_meals = to_pos_int(argv[5]);

	data->philos = malloc(data->philo_count * sizeof(pthread_t));
	if (!data->philos)
		return (false);
	data->forks = malloc(data->philo_count * sizeof(mutex_t));
	if (!data->forks)
		return (false);

	if (create_philos(data) == false)
		return (false);
	return (true);
}
