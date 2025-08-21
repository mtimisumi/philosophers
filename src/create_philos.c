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

t_philo	init_philo(int philo_id, int meal_count,
		mutex_t *left_fork, mutex_t *right_fork)
{
	t_philo	philo;

	philo.philo_id = philo_id;
	philo.left_fork = left_fork;
	philo.right_fork = right_fork;
	philo.meal_count = meal_count;
	philo.dead = false;
	return (philo);
}

bool	create_philos(t_philo *philo, int philo_count,
		int meal_count, mutex_t *forks)
{
	mutex_t	*left_fork;
	mutex_t	*right_fork;
	int		i;

	philo = malloc(philo_count * sizeof(t_philo));
	if (!philo)
		return (false);
	left_fork = &forks[philo_count - 1];
	i = 0;
	while (i < philo_count)
	{
		right_fork = &forks[i];
		philo[i] = init_philo(i, meal_count, left_fork, right_fork);
		left_fork =right_fork;
		i++;
	}
	return (true);
}

