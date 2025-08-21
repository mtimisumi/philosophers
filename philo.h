/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:20:25 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/21 15:47:45 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

# define mutex_t pthread_mutex_t

typedef struct	s_philo
{
	int		philo_id;
	int		meal_count;
	mutex_t	*left_fork;
	mutex_t	*right_fork;
	bool	dead;
}				t_philo;

typedef struct	s_data
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		amount_of_meals;
	mutex_t	*meals;
	t_philo	*philo;
}				t_data;


//validate
bool	are_valid_args(char **argv);

//utils
bool	init_data(t_data *data, char **argv);

//create philos
bool	create_philos(t_philo *philo, int philo_count,
		int meal_count, mutex_t *forks);

//diner
bool	start_diner(t_data *data, pthread_t *philos, mutex_t *forks);
bool	end_diner(pthread_t *philos);
bool	cleanup_diner(mutex_t *forks, int count);


#endif
