/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:16:17 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 15:48:19 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	setup_diner(t_data *data)
{
	t_philo		*philo;
	pthread_t	*philos;
	mutex_t		*forks;

	philos = malloc(data->philo_count * sizeof(pthread_t));
	if (!philos)
		return (false);
	forks = malloc(data->philo_count * sizeof(mutex_t));
	if (!forks)
		return (false);
	philo = NULL;
	if (create_philos(philo, data->philo_count, data->amount_of_meals, forks) == false)
		return (false);
	data->philo = philo;
	if (start_diner(data, philos, forks) == false)
		return (false);
	if (end_diner(philos) == false)
		return (false);
	if (cleanup_diner(forks, data->philo_count) == false)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc == 5 || argc == 6)
	{
		if (init_data(&data, argv) == true)
			return (setup_diner(&data));
		return (1);
	}
	return (printf("Invalid amount of args\n"), 1);
}
