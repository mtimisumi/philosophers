#include "philo.h"

t_data	*init_data_node(pthread_t philo, int id,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->philo = philo;
	new->id = id;
	new->left_fork = left_fork;
	new->right_fork = right_fork;
	new->next = NULL;
	return (new);
}

void	add_data_node_back(t_data **data, t_data *new)
{
	t_data	*temp;

	if (*data == NULL)
	{
		*data = new;
		return ;
	}
	temp = *data;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_data	*init_data_list(t_data **data, pthread_t *philo,
		pthread_mutex_t *mutex, int philo_count)
{
	t_data			*new;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				i;

	left_fork = &mutex[philo_count - 1];
	new = NULL;
	i = 0;
	while (i < philo_count)
	{
		right_fork = &mutex[i];
		new = init_data_node(philo[i], i, left_fork, right_fork);
		if (!new)
			return (NULL);
		add_data_node_back(data, new);
		left_fork = &mutex[i];
		i++;
	}
	return (*data);
}

void	*task(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(data->left_fork);
	pthread_mutex_lock(data->right_fork);
	printf("id %d: Taking the forks\n", data->id);
	sleep(3);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	return (NULL);
}

void	loop(t_data *data, int philo_count)
{
	(void)philo_count;
	pthread_mutex_init(data->left_fork, NULL);
	while (data)
	{
		if (data->next != NULL)
			pthread_mutex_init(data->right_fork, NULL);
		pthread_create(&data->philo, NULL, &task, data);
		data = data->next;
	}
}

void	print_data(t_data *data)
{
	while (data)
	{
		printf("philo: %d\n", data->id);
		printf("left_fork : %p\n", data->left_fork);
		printf("right_fork: %p\n", data->right_fork);
		data = data->next;
	}
}
int	philo(char **argv)
{
	(void)argv;
	pthread_t		*philo;
	pthread_mutex_t	*mutex;
	t_data			*data;
	int				philo_count;

	philo_count = to_pos_int(argv[1]);
	printf("philo_count: %d\n", philo_count);
	philo = malloc(philo_count * sizeof(pthread_t));
	if (!philo)
		return (1);
	mutex = malloc (philo_count * sizeof(pthread_mutex_t));
	if (!mutex)
		return (1);
	data = NULL;
	if (init_data_list(&data, philo, mutex, philo_count) == NULL)
		return (1);
	//free philo and mutex
	// print_data(data);
	loop(data, philo_count);
	return (0);
}


int	main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		if (are_valid_args(argv) == false)
			return (1);
		return (philo(argv));
	}
	else
		return (printf("Invalid amount of arguments\n"), 1);
}
