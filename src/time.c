#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_cur_time(long start_time)
{
	return (get_time_in_ms() - start_time);
}

void	ft_usleep(long mili_secs)
{
	long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < mili_secs)
		usleep(500);
}


