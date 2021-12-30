#include "philo.h"

int	main(int argc, char **argv)
{
	t_threadinfo	*infos;
	t_parameters	*parameters;
	t_philosopher	**philosophers;
	pthread_mutex_t	**forks;
	pthread_t		*threads;

	if ((argc != 5 && argc != 6) || check_arg(argv) == -1)
		return (-1);
	parameters = malloc(sizeof(t_parameters));
	init_parameters(parameters);
	set_parameters(parameters, argc, argv);
	philosophers = malloc(sizeof(t_philosopher) * parameters->nb_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * parameters->nb_philosophers);
	threads = malloc(sizeof(pthread_t) * parameters->nb_philosophers);
	parameters->start_time = current_timestamp();
	if (!create_philos(parameters, forks, philosophers))
		return (-1);
	infos = malloc(sizeof(t_threadinfo));
	infos->parameters = parameters;
	infos->philosophers = philosophers;
	infos->forks = forks;
	thread_main_create(infos, parameters, philosophers, forks, threads);
	free_all(philosophers, forks, parameters);
	free(infos);
	return (0);
}
