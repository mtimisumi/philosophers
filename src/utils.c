/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:53:01 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 16:40:40 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	data->philo_count = to_pos_int(argv[1]);
	data->time_to_die = to_pos_int(argv[2]);
	data->time_to_eat = to_pos_int(argv[3]);
	data->time_to_sleep = to_pos_int(argv[4]);
	data->amount_of_meals = to_pos_int(argv[5]);
	return (true);
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	if (data->diner)
	{
		if (pthread_mutex_destroy(data->diner) != 0)
			free(data->diner);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->philo)
	{
		if (data->philo->left_fork)
			free(data->philo->left_fork);
		if (data->philo->right_fork)
			free(data->philo->right_fork);
		free(data->philo);
		data->philo++;
	}
}
