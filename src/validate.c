#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

bool	is_pos_int(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '0')
		return (false);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	if (ft_strlen(s) > 10)
		return (false);
	if (ft_strlen(s) == 10 && ft_strcmp(s, "2147483647") > 0)
		return (false);
	return (true);
}

bool	are_valid_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_pos_int(argv[i]) == false)
		{
			printf("Invalid arg: %s\n", argv[i]);
			return (false);
		}
		i++;
	}
	return (true);
	
}

int	to_pos_int(char *s)
{
	int	i;
	int	nbr;

	if (!s)
		return (-1);
	i = 0;
	nbr = 0;
	while (s[i])
	{
		nbr = nbr + (s[i] - '0');
		if (s[i + 1] != '\0')
			nbr = nbr * 10;
		i++;
	}
	return (nbr);
}
