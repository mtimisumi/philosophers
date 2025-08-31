#include "philo.h"

bool	init_philo(t_philo *philo, int id, int left_fork, int right_fork)
{
	philo->id = id;
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
	philo->meal_count = 0;
	philo->last_meal = 0;
	philo->meal = NULL;
	philo->full = false;
	philo->data = NULL;
	return (true);
}

bool	create_philos(t_data *data)
{
	mutex_t	*meal;
	int		i;
	int		left_fork;
	int		right_fork;

	data->philo = malloc(data->philo_count * sizeof(t_philo));
	if (!data->philo)
		return (false);
	meal = malloc(data->philo_count * sizeof(mutex_t));
	if (!meal)
		return (false);

	left_fork = data->philo_count - 1;
	i = 0;
	while (i < data->philo_count)
	{
		right_fork = i;
		init_philo(&data->philo[i], i, left_fork, right_fork);
		data->philo[i].meal = &meal[i];
		data->philo[i].data = data;
		left_fork = right_fork;
		i++;
	}
	return (true);
}


bool	init_data(t_data *data, char **argv)
{
	if (are_valid_args(argv) == false)
		return (false);
	data->dead = false;
	data->full = 0;
	data->start_time = get_time_in_ms();
	data->philo_count = to_pos_int(argv[1]);
	data->time_to_die = to_pos_int(argv[2]);
	data->time_to_eat = to_pos_int(argv[3]);
	data->time_to_sleep = to_pos_int(argv[4]);
	data->amount_of_meals = to_pos_int(argv[5]);
	data->status = malloc(2 * sizeof(mutex_t));
	if (!data->status)
		return (false);
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

