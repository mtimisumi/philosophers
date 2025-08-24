#include "philo.h"

bool	setup_diner(t_data *data)
{
	if (allocate_for_philos(data) == false)
		return (false);
	if (allocate_for_forks(data) == false)
		return (false);
	if (create_philos(data) == false)
		return (false);
	if (start_diner(data) == false)
		return (false);
	if (end_diner(data) == false)
		return (false);
	// print_data(data);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		exitcode;

	memset(&data, 0, sizeof(t_data));
	if (argc == 5 || argc == 6)
	{
		if (init_data(&data, argv) == true)
		{
			exitcode = setup_diner(&data);
			// cleanup(&data);
			return (exitcode);
		}
		return (1);
	}
	return (printf("Invalid amount of args\n"), 1);
}
