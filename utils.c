/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:11:30 by jumaison          #+#    #+#             */
/*   Updated: 2022/01/03 16:07:59 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if ((*arg < '0' || *arg > '9'))
		{
			ft_putstr_fd("Error: Invalid args\n", 1);
			return (-1);
		}
		arg++;
	}
	return (0);
}

int	check_arg(char **argv)
{
	int				i;
	long long int	nb;

	i = 1;
	nb = 0;
<<<<<<< HEAD
	nb = ft_atoll(argv[1]);
	if (nb == 0)
	{
		printf("Error: 0 philosophers\n");
		return (-1);
	}
=======
>>>>>>> 786343c4bb78f0d6c0f7422056271d398b4827ef
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
