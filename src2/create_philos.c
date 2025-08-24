/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:26 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 15:45:06 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int id, mutex_t *left_fork, mutex_t *right_fork)
{
	t_philo	philo;

	philo.id = id;
	philo.meal_count = 0;
	philo.left_fork = left_fork;
	philo.right_fork = right_fork;
	philo.dead = false;
	return (philo);
}

bool	create_philos(t_philo **philo, int philo_count, mutex_t *forks)
{
	mutex_t	*left_fork;
	mutex_t	*right_fork;
	int		i;

	*philo = malloc(philo_count * sizeof(t_philo));
	if (!*philo)
		return (false);
	left_fork = &forks[philo_count - 1];
	i = 0;
	while (i < philo_count)
	{
		right_fork = &forks[i];
		(*philo)[i] = init_philo(i, left_fork, right_fork);
		left_fork =right_fork;
		i++;
	}
	return (true);
}

