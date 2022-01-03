/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:11:32 by jumaison          #+#    #+#             */
/*   Updated: 2022/01/03 16:40:48 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_threadinfo	infos;
	t_parameters	parameters;
	t_philosopher	**philosophers;
	pthread_mutex_t	**forks;
	pthread_t		*threads;

	if ((argc != 5 && argc != 6) || check_arg(argv) == -1)
		return (-1);
	init_parameters(&parameters);
	set_parameters(&parameters, argc, argv);
	philosophers = malloc(sizeof(t_philosopher) * parameters.nb_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * parameters.nb_philosophers);
	threads = malloc(sizeof(pthread_t) * parameters.nb_philosophers);
	parameters.start_time = current_timestamp();
	if (!create_philos(&parameters, forks, philosophers))
		return (-1);
	infos.philosophers = philosophers;
	infos.forks = forks;
	infos.parameters = &parameters;
	thread_main_create(infos, threads);
	free_all(&parameters, infos);
	free(threads);
	return (0);
}
