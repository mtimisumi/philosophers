#include "philo.h"

void	monitor_philos(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->philo_count)
			i = 0;
		if (is_dead(data, i) == true)
		{
			pthread_mutex_lock(&data->status[DEAD]);
			data->dead = true;
			printf("%-6ld %-3d has died\n", get_cur_time(data->start_time), i);
			pthread_mutex_unlock(&data->status[DEAD]);
			break ;
		}
		pthread_mutex_lock(&data->status[FULL]);
		if (data->full == data->philo_count)
		{
			printf("\nall philosophers are full\n");
			break ;
		}
		pthread_mutex_unlock(&data->status[FULL]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of args\n"), 1);
	if (init_data(&data, argv) == false)
		return (cleanup(&data), 1);
	if (start_diner(&data) == false)
		return (cleanup(&data), 1);
	monitor_philos(&data);
	if (end_diner(&data) == false)
		return (cleanup(&data), 1);
	cleanup(&data);
	return (0);

}
