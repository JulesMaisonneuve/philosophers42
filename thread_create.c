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
    // free(forks);
    // free(philos);
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
			// printf("KEK");
			// if (check_meals(infos->philosophers, infos->parameters) == -1)
			// {
			// 	printf("UN PHILOSOPHE A GRAILLE UN MAX");
			// 	infos->max_meals = 1;
			// 	// free_all(infos->philosophers, infos->forks, infos->parameters);
			// 	return (ptr);
			// }
		}
		sleeping(infos->philosophers[infos->nb_philo], infos->parameters);
		thinking(infos->philosophers[infos->nb_philo], infos->parameters);
	}
	return (ptr);
}

int	thread_main_create(t_threadinfo	*infos, t_parameters *params, t_philosopher **philos, pthread_mutex_t **forks, pthread_t *threads)
{
    int i;
    pthread_t monitor = 0;

    pthread_create(&monitor, NULL, *check_death_meals, (void *) infos);
	i = 0;
	while (i < params->nb_philosophers)
	{
		infos = malloc(sizeof(t_threadinfo));
		infos->parameters = params;
		infos->philosophers = philos;
		infos->forks = forks;
		infos->nb_philo = i;
		pthread_create(&threads[i], NULL, *thread_main, (void *) infos);
		i++;
	}
    pthread_join(monitor, NULL);
	return (0);
}