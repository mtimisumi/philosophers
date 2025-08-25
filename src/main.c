#include "philo.h"

void	monitor_philos(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->philo_count)
			i = 0;
		if ((get_cur_time(data->start_time) - data->philo[i].last_meal) > data->time_to_die)
		{
			pthread_mutex_lock(&data->status[0]);
			data->dead = true;
			printf("%-6ld %-3d has died\n", get_cur_time(data->start_time), i);
			pthread_mutex_unlock(&data->status[0]);
			break ;
		}
		pthread_mutex_lock(&data->status[1]);
		if (data->full == data->philo_count)
		{
			printf("\nall philosophers are full\n");
			break ;
		}
		pthread_mutex_unlock(&data->status[1]);
		i++;
	}
}

bool	philo(t_data *data)
{
	if (start_diner(data) == false)
		return (false);
	monitor_philos(data);
	if (end_diner(data) == false)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of args\n"), 1);
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argv) == false || philo(&data) == false)
		return (cleanup(&data), 1);
	return (cleanup(&data), 0);
}
