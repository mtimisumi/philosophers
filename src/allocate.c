/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:42:50 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 14:50:08 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	allocate_data(t_data *data)
// {
// 	data = malloc(1 * sizeof(t_data));
// 	if (!data)
// 		return (false);
// 	return (true);
// }

// bool	allocate_philo(t_philo *philo)
// {
// 	philo = malloc(1 * sizeof(t_philo));
// 	if (!philo)
// 		return (false);
// 	return (true);
// }

bool	allocate_philos(pthread_t *philos, int philo_count)
{
	philos = malloc(philo_count * sizeof(pthread_t));
	if (!philos)
		return (false);
	return (true);
}

bool	allocate_forks(pthread_mutex_t *forks, int philo_count)
{
	forks = malloc(philo_count * sizeof(pthread_mutex_t));
	if (!forks)
		return (false);
	return (true);
}
