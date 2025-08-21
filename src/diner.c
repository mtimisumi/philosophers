/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:28:36 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 16:02:28 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rountine(void *arg)
{
	(void)arg;
	return (NULL);
}

bool	start_diner(t_data *data, pthread_t *philos, mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (philos[i])
	{
		if (pthread_create(&philos[i], NULL, &rountine, data) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool	end_diner(pthread_t *philos, mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

