#include "philo.h"

void	print_threads(pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("thread %d: %p\n", i, &threads[i]);
		i++;
	}
}

void	print_mutexes(mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("mutex %d: %p\n", i, &forks[i]);
		i++;
	}
}

void	print_philo(t_philo philo)
{
	printf("philo id: %d\n", philo.id);
	printf("meal count: %d\n", philo.meal_count);
	printf("left fork: %p\n", philo.left_fork);
	printf("right fork: %p\n", philo.right_fork);
	if (philo.dead == true)
		printf("dead\n");
	else
		printf("alive\n");

}

void	print_data(t_data *data)
{
	int	i;
	if (!data)
		return ;
	printf("philo count: %d\n", data->philo_count);
	printf("time to die: %d\n", data->time_to_die);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	printf("amount of meals: %d\n", data->amount_of_meals);
	printf("diner: %p\n", data->diner);
	printf("----------------------\n");
	print_threads(data->philos, data->philo_count);
	printf("----------------------\n");
	print_mutexes(data->forks, data->philo_count);
	printf("----------------------\n");
	i = 0;
	while (i < data->philo_count)
	{
		print_philo(data->philo[i]);
		i++;
	}	
}
