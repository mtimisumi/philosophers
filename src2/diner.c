/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:28:36 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 17:42:35 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	// int	i;

	
	philo = (t_philo *)arg;
	printf("id: %d\n", philo->id);
	printf("leftfork: %p\n", philo->left_fork);
	printf("rightfork: %p\n", philo->right_fork);
	printf("\n");

	// i = 0;
	// while (i < data->philo_count)
	// {
	// 	pthread_mutex_lock(data->philo->left_fork);
	// 	pthread_mutex_lock(data->philo->right_fork);
	// 	printf("locking with philo number %d\n", i);
	// 	sleep(1);
	// 	pthread_mutex_unlock(data->philo->left_fork);
	// 	pthread_mutex_unlock(data->philo->right_fork);
	// 	i++;
	// }
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
	while (i < data->philo_count)
	{
		if (pthread_create(&philos[i], NULL, &routine, &data->philo[i]) != 0)
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

