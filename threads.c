/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:43:35 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/10 14:37:34 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mails = 0;
pthread_mutex_t mutex;

void	*message()
{
	pthread_mutex_lock(&mutex);
	printf("Start of thread\n");
	for (int i = 0; i < 10000000; i++)
	{
		// pthread_mutex_lock(&mutex);
		mails++;
		// pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_unlock(&mutex);
	printf("End of thread\n");
}

int	main(void)
{
	pthread_t	t1, t2, t3, t4;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &message, NULL) != 0)
		printf("Error creating thread t1\n");
	if (pthread_create(&t2, NULL, &message, NULL) != 0)
		printf("Error creating thread t2\n");
	if (pthread_create(&t3, NULL, &message, NULL) != 0)
		printf("Error creating thread t3\n");
	if (pthread_create(&t4, NULL, &message, NULL) != 0)
		printf("Error creating thread t4\n");
	if (pthread_join(t1, NULL) != 0)
		printf("Join error t1\n");
	if (pthread_join(t2, NULL) != 0)
		printf("Join error t2");
	if (pthread_join(t3, NULL) != 0)
		printf("Join error t3\n");
	if (pthread_join(t4, NULL) != 0)
		printf("Join error t4");
	pthread_mutex_destroy(&mutex);
	printf("number of mails: %d\n", mails);
	return (0);
}
