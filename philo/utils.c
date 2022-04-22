#include "philo.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long int	result;
	int					negative;
	size_t				i;

	result = 0;
	negative = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > 2147483647 && negative == 1)
			return (-1);
		else if (result > 2147483648 && negative == -1)
			return (0);
	}
	return ((int)(result * negative));
}
