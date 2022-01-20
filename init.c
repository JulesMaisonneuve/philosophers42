/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:12:26 by jumaison          #+#    #+#             */
/*   Updated: 2022/01/20 22:05:28 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_parameters(t_parameters *parameters)
{
	parameters->nb_philosophers = 0;
	parameters->time_to_die = 0;
	parameters->time_to_sleep = 0;
	parameters->time_to_eat = 0;
	parameters->nb_meals = -1;
	parameters->start_time = 0;
}

void	init_philosopher(t_philosopher *philosopher)
{
	philosopher->eating = 0;
	philosopher->thinking = 0;
	philosopher->sleeping = 0;
	philosopher->nb = 0;
	philosopher->dead = false;
	philosopher->last_meal = current_timestamp();
	philosopher->nb_meals = 0;
	philosopher->struct_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philosopher->struct_lock, NULL);
}

void	set_parameters(t_parameters *parameters, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		parameters->nb_philosophers = ft_atoi(argv[1]);
		parameters->time_to_die = ft_atoi(argv[2]);
		parameters->time_to_eat = ft_atoi(argv[3]);
		parameters->time_to_sleep = ft_atoi(argv[4]);
	}
	if (argc == 6)
	{
		parameters->nb_meals = ft_atoi(argv[5]);
	}
}

int	create_philos(t_parameters *parameters, pthread_mutex_t **forks,
t_philosopher **philosophers)
{
	int	i;

	i = 0;
	while (i < parameters->nb_philosophers)
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		if (philosophers[i] == NULL)
			return (-1);
		init_philosopher(philosophers[i]);
		philosophers[i]->nb = i;
		i++;
	}
	i = 0;
	while (i < parameters->nb_philosophers)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
			return (-1);
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (1);
}
