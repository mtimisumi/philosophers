/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:16:17 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 14:56:24 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_diner(t_data *data, t_philo *philo)
{
	while ()
}

bool	setup_diner(t_data *data, char **argv)
{
	t_philo			*philo;
	pthread_t		*philos;
	pthread_mutex_t	*forks;

	if (allocate_philos(philos, data->philo_count) == false)
		return (false);
	if (allocate_forks(forks, data->philo_count) == false)
		return (false);
	philo = NULL;
	if (create_philos(&philo, data->philo_count, data->amount_of_meals, forks) == false)
		return (false);
	if (start_diner(data, philo) == false)
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
			return (setup_diner(&data, argv));
		return (1);
	}
	return (printf("Invalid amount of args\n"), 1);
}
