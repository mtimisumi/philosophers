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

bool	check_dead_status(t_data *data)
{
	pthread_mutex_lock(&data->status[0]);
	if (data->dead == true)
	{
		pthread_mutex_unlock(&data->status[0]);
		return (true);
	}
	pthread_mutex_unlock(&data->status[0]);
	return (false);
}

void	print_msg(char *msg, long start_time, int id)
{
	printf("%-6ld %-3d %s\n", get_cur_time(start_time), id, msg);
}

