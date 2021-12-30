#include "philo.h"

bool	is_someone_dead(t_philosopher **philosophers, int nb_philosophers)
{
	int	i;

	i = 0;
	while (i < nb_philosophers)
	{
		if (philosophers[i]->dead)
			return (true);
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
		if (philosophers[i]->nb_meals != parameters->nb_meals)
			return (0);
		i++;
	}
	return (1);
}

bool	is_starved_to_death(t_philosopher *philo, t_parameters *params)
{
	long long	actual_time;

	actual_time = current_timestamp();
	if ((actual_time - philo->last_meal) > params->time_to_die)
	{
		philo->dead = true;
		printf("-%lld- [%d] died\n",
			(current_timestamp() - params->start_time), philo->nb + 1);
		return (true);
	}
	return (false);
}

void	*check_death(void *ptr)
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
			i++;
		}
	}
	return (ptr);
}
