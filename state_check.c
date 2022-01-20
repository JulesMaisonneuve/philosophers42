/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:11:42 by jumaison          #+#    #+#             */
/*   Updated: 2022/01/20 22:50:24 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_everyone_fed(t_philosopher **philosophers, t_parameters *params)
{
	int	i;

	i = 0;
	if (params->nb_meals > 0)
	{
		while (i < params->nb_philosophers)
		{
			if (philosophers[i]->nb_meals < params->nb_meals)
			{
				return (false);
			}
			i++;
		}
		return (true);
	}
	else
		return (false);
}

bool	is_someone_dead_fed(t_philosopher **philosophers, int nb_philosophers,
			t_parameters *params)
{
	int	i;

	i = 0;
	while (i < nb_philosophers)
	{
		pthread_mutex_lock(philosophers[i]->struct_lock);
		if (philosophers[i]->dead)
		{
			pthread_mutex_unlock(philosophers[i]->struct_lock);
			return (true);
		}
		else if (is_everyone_fed(philosophers, params))
		{
			pthread_mutex_unlock(philosophers[i]->struct_lock);
			return (true);
		}
		pthread_mutex_unlock(philosophers[i]->struct_lock);
		i++;
	}
	return (false);
}

int	check_meals(t_philosopher **philosophers, t_parameters *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->nb_philosophers)
	{
		if (philosophers[i]->nb_meals == parameters->nb_meals)
			return (-1);
		i++;
	}
	return (0);
}

bool	is_starved_to_death(t_philosopher *philo, t_parameters *params)
{
	long long	actual_time;
	
	actual_time = current_timestamp();
	pthread_mutex_lock(philo->struct_lock);
	if ((actual_time - philo->last_meal) > params->time_to_die)
	{
		philo->dead = true;
		pthread_mutex_unlock(philo->struct_lock);
		printf("-%lld- [%d] died\n",
			(current_timestamp() - params->start_time), philo->nb + 1);
		return (true);
	}
	pthread_mutex_unlock(philo->struct_lock);
	return (false);
}

void	*check_death_meals(void *ptr)
{
	t_threadinfo	*infos;
	int				i;

	infos = (t_threadinfo *) ptr;
	while (1)
	{
		i = 0;
		while (i < infos->parameters->nb_philosophers)
		{
			if (is_starved_to_death(infos->philosophers[i], infos->parameters))
				return (ptr);
			else if (is_everyone_fed(infos->philosophers, infos->parameters))
			{
				return (ptr);
			}
			i++;
		}
	}
	return (ptr);
}
