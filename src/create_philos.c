/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:26 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 14:56:14 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int philo_id, int meal_count,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	t_philo	*new;

	new = malloc(1 * sizeof(t_philo));
	if (!new)
		return (NULL);
	new->philo_id = philo_id;
	new->left_fork = left_fork;
	new->right_fork = right_fork;
	new->meal_count = meal_count;
	new->dead = false;
	new->next = NULL;
	return (new);
}

void	add_philo_to_back(t_philo **philo, t_philo *new)
{
	t_philo	*temp;

	if (*philo == NULL)
	{
		*philo = new;
		return ;
	}
	temp = *philo;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

bool	create_philos(t_philo **philo, int philo_count,
		int meal_count, pthread_mutex_t *forks)
{
	t_philo			*new;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				i;

	new = NULL;
	left_fork = &forks[philo_count - 1];
	i = 0;
	while (i < philo_count)
	{
		right_fork = &forks[i];
		new = init_philo(i, meal_count, left_fork, right_fork);
		if (!new)
			return (false);
		add_philo_to_back(philo, new);
		left_fork = right_fork;
		i++;
	}
	return (true);
}
