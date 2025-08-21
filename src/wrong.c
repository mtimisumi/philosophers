/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:19:17 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 14:15:16 by mmisumi          ###   ########.fr       */
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

	philo = NULL;
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

void	cleanup(t_philo *philo, pthread_t *philos, pthread_mutex_t *forks)
{
	(void)philo;
	(void)philos;
	(void)forks;
	return ;
}

bool	setup_diner(t_data *data, t_philo *philo, pthread_t *philos, pthread_mutex_t *forks)
{
	philo = malloc(data->philo_count * sizeof(t_philo));
	if (!philo)
		return (false);
	philos = malloc(data->philo_count * sizeof(pthread_t));
	if (!philos)
		return (false);
	forks = malloc(data->philo_count * sizeof(pthread_mutex_t));
	if (!forks)
		return (false);
	if (create_philos(&philo, data->philo_count, data->amount_of_meals, forks) == false)
		return (cleanup(philo, philos, forks), false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data			*data;
	t_philo			*philo;
	pthread_t		*philos;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of arguments\n"), 1);
	data = NULL;
	if (init_data(data, argv) == false)
		return (1);
	philo = NULL;
	setup_diner(data, philo, philos, forks);
	printf("here\n");
	return (0);
}