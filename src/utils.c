#include "philo.h"

bool	allocate_for_philos(t_data *data)
{
	data->philos = malloc(data->philo_count * sizeof(pthread_t));
	if (!data->philos)
		return (false);
	return (true);
}

bool	allocate_for_forks(t_data *data)
{
	data->forks = malloc(data->philo_count * sizeof(mutex_t));
	if (!data->forks)
		return (false);
	return (true);
}

int	to_pos_int(char *s)
{
	int	i;
	int	nbr;

	if (!s)
		return (-1);
	i = 0;
	nbr = 0;
	while (s[i])
	{
		nbr = nbr + (s[i] - '0');
		if (s[i + 1] != '\0')
			nbr = nbr * 10;
		i++;
	}
	return (nbr);
}

bool	init_data(t_data *data, char **argv)
{
	if (are_valid_args(argv) == false)
		return (false);
	data->philo_count = to_pos_int(argv[1]);
	data->time_to_die = to_pos_int(argv[2]);
	data->time_to_eat = to_pos_int(argv[3]);
	data->time_to_sleep = to_pos_int(argv[4]);
	data->amount_of_meals = to_pos_int(argv[5]);
	return (true);
}

