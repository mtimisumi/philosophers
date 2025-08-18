/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:47:53 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/10 17:37:19 by mmisumi          ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_mutex_t	mutex;
}				t_philo;


typedef struct	s_data
{
	pthread_t		philo;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*next;
}				t_data;

//utils
int		to_pos_int(char *s);

//validate
bool	are_valid_args(char **argv);

#endif
