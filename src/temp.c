#include "philo.h"

void	print_thread_address(pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("thread %d: %p\n", i, &threads[i]);
		i++;
	}
}

void	print_mutex_address(mutex_t *mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("mutex %d: %p\n", i, &mutexes[i]);
		i++;
	}
}

void	print_philo(t_philo *philo)
{
	printf("philo id: %d\n", philo->id);
	printf("left fork: %d\n", philo->left_fork);
	printf("right fork: %d\n", philo->right_fork);
	printf("meal count: %d\n", philo->meal_count);
	if (philo->dead == false)
		printf("philo: alive\n");
	else
		printf("philo: dead\n");
	printf("------------------\n");
}

void	print_data(t_data *data)
{
	printf("philo count: %d\n", data->philo_count);
	printf("time to die: %d\n", data->time_to_die);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	printf("amount of meals: %d\n", data->amount_of_meals);
	printf("----------------------\n");
	print_thread_address(data->philos, data->philo_count);
	printf("----------------------\n");
	print_mutex_address(data->forks, data->philo_count);
	printf("----------------------\n");
}