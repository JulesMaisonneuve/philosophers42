#include "philo.h"

void	free_all(t_philosopher **philos,
	pthread_mutex_t **forks, t_parameters *params)
{
	int	i;

	i = 0;
	while (i < params->nb_philosophers)
	{
		free(forks[i]);
		free(philos[i]);
		i++;
	}
	free(params);
}

void	*thread_main(void *ptr)
{
	t_threadinfo	*infos;

	infos = (t_threadinfo *) ptr;
	while (!is_someone_dead(infos->philosophers,
			infos->parameters->nb_philosophers))
	{
		eating(infos->philosophers[infos->nb_philo],
			infos->forks, infos->parameters);
		if (infos->parameters->nb_meals > 0)
		{
			if (check_meals(infos->philosophers, infos->parameters))
			{
				free_all(infos->philosophers, infos->forks, infos->parameters);
				return (0);
			}
		}
		sleeping(infos->philosophers[infos->nb_philo], infos->parameters);
		thinking(infos->philosophers[infos->nb_philo], infos->parameters);
	}
	return (ptr);
}

int	main(int argc, char **argv)
{
	t_threadinfo	*infos;
	int				i;
	t_parameters	*parameters;

	parameters = malloc(sizeof(t_parameters));
	init_parameters(parameters);
	set_parameters(parameters, argc, argv);
	t_philosopher	*philosophers[parameters->nb_philosophers];
	pthread_mutex_t	*forks[parameters->nb_philosophers];
	pthread_t		threads[parameters->nb_philosophers];
	pthread_t		monitor;

	if (argc > 8)
		return (-1);
	parameters->start_time = current_timestamp();
	if (!create_philos(parameters, forks, philosophers))
		return (-1);
	infos = malloc(sizeof(t_threadinfo));
	infos->parameters = parameters;
	infos->philosophers = philosophers;
	infos->forks = forks;
	pthread_create(&monitor, NULL, *check_death, (void *) infos);
	i = 0;
	while (i < parameters->nb_philosophers)
	{
		infos = malloc(sizeof(t_threadinfo));
		infos->parameters = parameters;
		infos->philosophers = philosophers;
		infos->forks = forks;
		infos->nb_philo = i;
		pthread_create(&threads[i], NULL, *thread_main, (void *) infos);
		i++;
	}
	pthread_join(monitor, NULL);
	free_all(philosophers, forks, parameters);
	free(infos);
	return (0);
}