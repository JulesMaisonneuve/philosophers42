/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:11:14 by jumaison          #+#    #+#             */
/*   Updated: 2022/01/03 17:02:40 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_parameters *params, t_threadinfo infos)
{
	int	i;

	i = 0;
	while (i < params->nb_philosophers)
	{
		free(infos.philosophers[i]);
		free(infos.forks[i]);
		i++;
	}
	free(infos.forks);
	free(infos.philosophers);
}

void	*thread_main(void *ptr)
{
	t_threadinfo	*infos;

	infos = (t_threadinfo *) ptr;
	while (!is_someone_dead(infos->philosophers,
			infos->parameters->nb_philosophers) && !check_meals(infos->philosophers, infos->parameters))
	{
		if (!is_someone_dead(infos->philosophers, infos->parameters->nb_philosophers) && !check_meals(infos->philosophers, infos->parameters))
			eating(infos->philosophers[infos->nb_philo], infos->forks, infos->parameters, infos);
		if (!is_someone_dead(infos->philosophers, infos->parameters->nb_philosophers) && !check_meals(infos->philosophers, infos->parameters))
			sleeping(infos->philosophers[infos->nb_philo], infos->parameters);
		if (!is_someone_dead(infos->philosophers, infos->parameters->nb_philosophers) && !check_meals(infos->philosophers, infos->parameters))
			thinking(infos->philosophers[infos->nb_philo], infos->parameters);
	}
	free(infos);
	return (ptr);
}

int	thread_main_create(t_threadinfo	infos, pthread_t *threads)
{
    int i;
    pthread_t monitor = 0;
	t_threadinfo *thread_info;

    pthread_create(&monitor, NULL, *check_death_meals, (void *) &infos);
	i = 0;
	while (i < infos.parameters->nb_philosophers)
	{
		thread_info = malloc(sizeof(t_threadinfo));
		thread_info->nb_philo = i;
		thread_info->forks = infos.forks;
		thread_info->philosophers = infos.philosophers;
		thread_info->parameters = infos.parameters;
		pthread_create(&threads[i], NULL, *thread_main, (void *) thread_info);
		usleep(100);
		i++;
	}
    pthread_join(monitor, NULL);
	i = 0;
	while (i < infos.parameters->nb_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
