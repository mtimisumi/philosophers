#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>

# define mutex_t pthread_mutex_t
typedef struct s_data	t_data;

typedef struct	s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
	int		meal_count;
	long	last_meal;
	mutex_t	*meal;
	bool	full;
	t_data	*data;
}				t_philo;

typedef struct	s_data
{
	bool		dead;
	int			full;
	long		start_time;
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			amount_of_meals;
	mutex_t		*status;
	pthread_t	*philos;
	mutex_t		*forks;
	t_philo		*philo;
}				t_data;

//utils
bool	check_dead_status(t_data *data);
int		to_pos_int(char *s);
void	print_msg(char *msg, long start_time, int id);


//cleanup
void	cleanup(t_data *data);
void	detach_threads(t_data *data, int i);
void	destroy_mutexes(t_data *data, int i);


//initialize
bool	init_data(t_data *data, char **argv);

//validate
bool	are_valid_args(char **argv);

//temp
void	print_philo(t_philo *philo);
void	print_data(t_data *data);

//diner
bool	start_diner(t_data *data);
bool	end_diner(t_data *data);

//time
long	get_time_in_ms(void);
bool	ft_usleep(t_data *data, long mili_secs);
long	get_cur_time(long start_time);

//routine
void	*routine(void *arg);

#endif
