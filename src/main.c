#include "philo.h"

void	cleanup(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

int	philo(char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argv) == false)
		return (1);
	data.philos = malloc(data.philo_count * sizeof(pthread_t));
	if (!data.philos)
		return (1);
	data.forks = malloc(data.philo_count * sizeof(mutex_t));
	if (!data.forks)
		return (1);
	if (create_philos(&data) == false)
		return (1);
	if (start_diner(&data) == false)
		return (1);
	if (end_diner(&data) == false)
		return (1);
	cleanup(&data);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of args\n"), 1);
	return (philo(argv));
}
