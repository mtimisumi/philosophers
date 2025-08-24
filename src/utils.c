#include "philo.h"

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
	data->start_time = get_time_in_ms();
	data->philo_count = to_pos_int(argv[1]);
	data->time_to_die = to_pos_int(argv[2]);
	data->time_to_eat = to_pos_int(argv[3]);
	data->time_to_sleep = to_pos_int(argv[4]);
	data->amount_of_meals = to_pos_int(argv[5]);
	data->philo_died = malloc(1 * sizeof(mutex_t));
	if (!data->philo_died)
		return (false);
	return (true);
}

void	destroy_mutexes(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	free(data->forks);
	data->forks = NULL;
}

void	detach_threads(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_detach(data->philos[i]);
		i--;
	}
	free(data->philos);
	data->philos = NULL;
}


