#include "philo.h"

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

void	loop(t_data *data)
{
	t_data	*temp;

	temp = data;
	pthread_mutex_init(data->left_fork, NULL);
	while (temp)
	{
		if (temp->next != NULL)
			pthread_mutex_init(temp->right_fork, NULL);
		pthread_create(&temp->philo, NULL, &task, temp);
		temp = temp->next;
	}
	temp = data;
	while (temp)
	{
		pthread_join(temp->philo, NULL);
		temp = temp->next;
	}
	temp = data;
	while (temp)
	{
		pthread_mutex_destroy(data->left_fork);
		temp = temp->next;
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
