#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

# define mutex_t pthread_mutex_t
typedef struct s_data	t_data;

typedef struct	s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
	int		meal_count;
	bool	dead;
	t_data	*data;
}				t_philo;

typedef struct	s_data
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			amount_of_meals;
	pthread_t	*philos;
	mutex_t		*forks;
	t_philo		*philo;
}				t_data;

//utils
bool	allocate_for_philos(t_data *data);
bool	allocate_for_forks(t_data *data);
bool	init_data(t_data *data, char **argv);

//validate
bool	are_valid_args(char **argv);

//create philos
bool	create_philos(t_data *data);

//temp
void	print_philo(t_philo *philo);
void	print_data(t_data *data);

//diner
bool	start_diner(t_data *data);
bool	end_diner(t_data *data);

#endif
