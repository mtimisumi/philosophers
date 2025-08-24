#include "philo.h"

void	init_philo(t_data *data, t_philo *philo, int id, int left_fork, int right_fork)
{
	philo->id = id;
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
	philo->meal_count = 0;
	philo->full = false;
	philo->dead = false;
	philo->data = data;
}

bool	create_philos(t_data *data)
{
	int	i;
	int	left_fork;
	int	right_fork;

	data->philo = malloc(data->philo_count * sizeof(t_philo));
	if (!data->philo)
		return (false);
	left_fork = data->philo_count - 1;
	i = 0;
	while (i < data->philo_count)
	{
		right_fork = i;
		init_philo(data, &data->philo[i], i, left_fork, right_fork);
		left_fork = right_fork;
		i++;
	}
	return (true);
}
