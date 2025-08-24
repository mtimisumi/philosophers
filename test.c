#include "philo.h"

int	main(void)
{
	struct timeval time;
	struct timeval now;
	gettimeofday(&time, NULL);
	printf("sec since jan 1970: %ld\n", (long)time.tv_sec);
	usleep(1000000);
	gettimeofday(&now, NULL);
	long dif = now.tv_sec - time.tv_sec;
	printf("secs since starting: %ld\n", (long)dif);
	printf("milisecs since then: %ld\n", (long)dif * 1000);
	printf("microsecs since then: %ld\n", (long)dif * 1000000);
	return (0);
}
