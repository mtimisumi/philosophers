#include "philo.h"

bool	check_dead_status(t_data *data)
{
	pthread_mutex_lock(&data->lock[DEAD]);
	if (data->dead == true)
	{
		pthread_mutex_unlock(&data->lock[DEAD]);
		return (true);
	}
	pthread_mutex_unlock(&data->lock[DEAD]);
	return (false);
}

bool	monitor_dead(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo[i].meal);
	if ((get_cur_time(data->start_time) - data->philo[i].last_meal) > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philo[i].meal);
		return (true);
	}
	pthread_mutex_unlock(&data->philo[i].meal);
	return (false);
	
}

void	print_action(t_data *data, int id, e_act act)
{
	char	*msg;

	pthread_mutex_lock(&data->lock[PRINT]);
	if (act == EAT)
		msg = "is eating\n";
	else if (act == SLEEP)
		msg = "is sleeping\n";
	else if (act == FORK)
		msg = "has taken a fork\n";
	else if (act == THINK)
		msg = "is thinking\n";
	if (check_dead_status(data) == false)
		printf("%-6ld %-3d %s", get_cur_time(data->start_time), id, msg);
	pthread_mutex_unlock(&data->lock[PRINT]);
}
