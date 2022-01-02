/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:11:39 by jumaison          #+#    #+#             */
/*   Updated: 2022/01/02 01:11:40 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}	

int	eating(t_philosopher *philos, pthread_mutex_t **forks, t_parameters *params)
{
	pthread_mutex_t	*own_fork;
	pthread_mutex_t	*next_fork;
	own_fork = forks[philos->nb];
	next_fork = forks[(philos->nb + 1) % params->nb_philosophers];
	if (pthread_mutex_lock(own_fork) != 0)
		return (-1);
	printf("-%lld- [%d] has taken his own fork\n",
		(current_timestamp() - params->start_time), philos->nb + 1);
	if (pthread_mutex_lock(next_fork) != 0)
		return (-1);
	printf("-%lld- [%d] has taken the next fork\n",
		(current_timestamp() - params->start_time), philos->nb + 1);
	printf("-%lld- [%d] is eating\n",
		(current_timestamp() - params->start_time), philos->nb + 1);
	usleep(params->time_to_eat * 1000);
	if (pthread_mutex_unlock(own_fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(next_fork) != 0)
		return (-1);
	philos->last_meal = current_timestamp();
	philos->nb_meals++;
	return (0);
}

void	thinking(t_philosopher *philosopher, t_parameters *parameters)
{
	printf("-%lld- [%d] is thinking\n",
		(current_timestamp() - parameters->start_time), philosopher->nb + 1);
}

void	sleeping(t_philosopher *philosopher, t_parameters *parameters)
{
	philosopher->sleeping = 1;
	printf("-%lld- [%d] is sleeping\n",
		(current_timestamp() - parameters->start_time), philosopher->nb + 1);
	usleep(parameters->time_to_sleep * 1000);
}
