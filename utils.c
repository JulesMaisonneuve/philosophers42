#include "philo.h"

long long int	ft_atoll(const char *str)
{
	long long int	nb;
	long long int	sign;
	int				i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		nb *= 10;
		nb += ((int)str[i] - '0');
		i++;
	}
	return (nb * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

int	is_valid_arg(char *arg)
{
	while (*arg)
	{
		if ((*arg < '0' || *arg > '9') && *arg != '+')
		{
			ft_putstr_fd("Error\n", 1);
			return (-1);
		}
		else if ((*arg == '+' && *(arg + 1) == '+'))
		{
			ft_putstr_fd("Error\n", 1);
			return (-1);
		}
		else if ((*arg == '-' || *arg == '+') && *(arg + 1) == '\0')
		{
			ft_putstr_fd("Error\n", 1);
			return (-1);
		}
		arg++;
	}
	return (0);
}

int	check_arg(char **argv)
{
	int	i;
	long long int	nb;

	i = 1;
	nb = 0;

	while (argv[i])
	{
		nb = ft_atoll(argv[i]);
		if (nb > 2147483647 || nb < -2147483648)
			return (-1);
		if (is_valid_arg(argv[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
