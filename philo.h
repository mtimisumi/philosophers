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

# define DEAD 0
# define FULL 1
# define MUST_EAT 2
#define PRINT 3

typedef struct	s_philo
{
	int		id;
	mutex_t	*left_fork;
	mutex_t	*right_fork;
	int		meal_count;
	long	last_meal;
	mutex_t	meal;
	t_data	*data;
}				t_philo;

typedef struct	s_data
{
	bool		dead;
	int			full;
	int			must_eat;
	long		start_time;
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			amount_of_meals;
	mutex_t		lock[4];
	pthread_t	*philos;
	mutex_t		*forks;
	t_philo		*philo;
}				t_data;

typedef enum	s_act
{
	EAT,
	SLEEP,
	FORK,
	THINK
}				e_act;

// initialize
bool	init_data(t_data *data, char **argv);

// validate
bool	are_valid_args(char **argv);
int		to_pos_int(char *s);

// utils
bool	check_dead_status(t_data *data);
void	print_action(t_data *data, int id, e_act act);
bool	monitor_dead(t_data *data, int i);

// time
long	get_time_in_ms(void);
long	get_cur_time(long start_time);
bool	ft_usleep(t_data *data, long mili_secs);

// cleanup
void	cleanup(t_data *data);
void	destroy_fork_mutex(t_data *data, int i);
void	detach_threads(t_data *data, int i);
void	destroy_meal_mutex(t_data *data, int i);
void	destroy_lock_mutex(t_data *data, int i);

// diner
bool	start_diner(t_data *data);
bool	end_diner(t_data *data);

// routine
void	*routine(void *arg);

#endif
