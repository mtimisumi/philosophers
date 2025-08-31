// #include "philo.h"

// void	destroy_mutexes(mutex_t *mutex, int i)
// {
// 	while (i >= 0)
// 	{
// 		pthread_mutex_destroy(&mutex[i]);
// 		i--;
// 	}
// 	free(mutex);
// 	mutex = NULL;
// }

// void	detach_threads(pthread_t *thread, int i)
// {
// 	while (i >= 0)
// 	{
// 		if (thread[i])
// 			pthread_detach(thread[i]);
// 		i--;
// 	}
// 	free(thread);
// 	thread = NULL;
// }

// void	cleanup(t_data *data)
// {
// 	if (data->status)
// 		destroy_mutexes(data->status, 1);
// 	if (data->philos)
// 		detach_threads(data->philos, data->philo_count - 1);
// 	if (data->forks)
// 		destroy_mutexes(data->forks, data->philo_count - 1);
// 	if (data->philo)
// 	{
// 		destroy_mutexes(data->philo->meal, data->philo_count - 1);
// 		free(data->philo);
// 	}
// }


#include "philo.h"

void	destroy_mutexes(mutex_t *mutex, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&mutex[i]);
		i--;
	}
	free(mutex);
}

void	detach_threads(pthread_t *thread, int created_count)
{
	int i = 0;
	
	// Only detach threads that were actually created
	while (i < created_count)
	{
		pthread_detach(thread[i]);
		i++;
	}
	free(thread);
}

void	cleanup(t_data *data)
{
	// Clean up status mutexes
	if (data->status)
	{
		destroy_mutexes(data->status, 1);
		data->status = NULL;
	}
	
	// Clean up philosopher threads - but we need to track how many were created
	if (data->philos)
	{
		// This is problematic - we don't know how many threads were created
		// The program should track created_threads_count
		free(data->philos);
		data->philos = NULL;
	}
	
	// Clean up fork mutexes
	if (data->forks)
	{
		destroy_mutexes(data->forks, data->philo_count - 1);
		data->forks = NULL;
	}
		
	// Clean up philosopher meal mutexes
	if (data->philo)
	{
		int i = 0;
		while (i < data->philo_count)
		{
			if (data->philo[i].meal)
			{
				pthread_mutex_destroy(data->philo[i].meal);
			}
			i++;
		}
		// Free the meal mutex array (allocated in create_philos)
		if (data->philo[0].meal)
			free(data->philo[0].meal);
		free(data->philo);
		data->philo = NULL;
	}
}