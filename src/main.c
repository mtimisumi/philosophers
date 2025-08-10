/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:45:29 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/10 18:01:13 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;

void	*message(void *arg)
{
	(void)arg;
	pthread_mutex_lock(&mutex);
	printf("Start of message\n");
	printf("End of message\n");
	pthread_mutex_unlock(&mutex);
	return (0);
}

int	philo(char **argv)
{
	pthread_t		*t;
	int				philo_count;
	int				i;

	philo_count = to_pos_int(argv[1]);
	t = malloc(philo_count * sizeof(pthread_t));
	if (!t)
		return (-1);
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < philo_count)
	{
		if (pthread_create(&t[i], NULL, &message, NULL) != 0)
			return (printf("Error creating thread t[%d]\n", i), -1);
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		if (pthread_join(t[i], NULL) != 0)
			return (printf("Error joining thread t[%d]\n", i), -1);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc == 5)
	{
		if (are_valid_args(argv) == false)
			return (1);
		return (philo(argv));
	}
	else
		return (printf("Invalid amount of arguments\n"), 1);
}
