#include "philo.h"

typedef	struct s_philosopher {
	int			eating;
	int			thinking;
	int			sleeping;
	int			nb;
	bool		dead;
	long long	last_meal;
	int			nb_meals;
}				t_philosopher;

typedef struct s_parameters
{
	int	nb_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
	long long start_time;
}				t_parameters;

typedef struct s_threadinfo
{
	t_philosopher	**philosophers;
	pthread_mutex_t	**forks;
	t_parameters	*parameters;
	int				nb_philo;
}				t_threadinfo;

long long current_timestamp() 
{
    struct timeval te; 

    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return (milliseconds);
}	

int	eating(t_philosopher *philosopher, pthread_mutex_t **forks, t_parameters *parameters)
{
	pthread_mutex_t *own_fork;
	pthread_mutex_t *next_fork;

	own_fork = forks[philosopher->nb];
	next_fork = forks[(philosopher->nb + 1) % parameters->nb_philosophers];
	if (pthread_mutex_lock(own_fork) != 0)
	{
		return (-1);
	}
	printf("-%lld- [%d] has taken his own fork\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
	if (pthread_mutex_lock(next_fork) != 0)
	{
		return (-1);
	}
	printf("-%lld- [%d] has taken the next fork\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
	printf("-%lld- [%d] is eating\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
	usleep(parameters->time_to_eat * 1000);
	if (pthread_mutex_unlock(own_fork) != 0)
	{
		return (-1);
	}
	printf("-%lld- [%d] has UNLOCKED his own fork\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
	if (pthread_mutex_unlock(next_fork) != 0)
	{
		return (-1);
	}
	printf("-%lld- [%d] has UNLOCKED the next fork\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
	philosopher->last_meal = current_timestamp();
	philosopher->nb_meals++;
	return (0);
}

void	thinking(t_philosopher *philosopher, t_parameters *parameters)
{
	
	printf("-%lld- [%d] is thinking\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
}

void	sleeping(t_philosopher *philosopher, t_parameters *parameters)
{
	philosopher->sleeping = 1;
	printf("-%lld- [%d] is sleeping\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
	usleep(parameters->time_to_sleep * 1000);
}

void	free_all(t_philosopher **philosophers, pthread_mutex_t **forks, t_parameters *parameters)
{
	int i;

	i = 0;
	while (i < parameters->nb_philosophers)
	{
		free(forks[i]);
		free(philosophers[i]);
		i++;
	}
	free(parameters);
}

bool	is_someone_dead(t_philosopher **philosophers, int nb_philosophers)
{
	int i;

	i = 0;
	while (i < nb_philosophers)
	{
		if (philosophers[i]->dead)
			return (true);
		i++;
	}
	return (false);
}

void	init_parameters(t_parameters *parameters)
{
	parameters->nb_philosophers = 0;
	parameters->time_to_die = 0;
	parameters->time_to_sleep = 0;
	parameters->time_to_eat = 0;
	parameters->nb_meals = 0;
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

int	check_meals(t_philosopher **philosophers, t_parameters *parameters)
{
	int i;

	i = 0;
	while (i < parameters->nb_philosophers)
	{
		if (philosophers[i]->nb_meals != parameters->nb_meals)
			return (0);
		i++;
	}
	return (1);
}

bool	is_starved_to_death(t_philosopher *philosopher, t_parameters *parameters)
{
	long long actual_time;

	actual_time = current_timestamp();
	// printf("diff: %lld  timetodie : %d  last_meal: %lld\n", (actual_time - philosopher->last_meal), parameters->time_to_die, philosopher->last_meal);
	if ((actual_time - philosopher->last_meal) > parameters->time_to_die)
	{
		philosopher->dead = true;
		printf("-%lld- [%d] died\n", (current_timestamp() - parameters->start_time), philosopher->nb + 1);
		return (true);
	}
	return (false);
}

void	*thread_main(void *ptr)
{
	t_threadinfo *infos;

	infos = (t_threadinfo *) ptr;
	while (!is_someone_dead(infos->philosophers, infos->parameters->nb_philosophers))
	{
		eating(infos->philosophers[infos->nb_philo], infos->forks, infos->parameters);
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

void	*check_death(void *ptr)
{
	t_threadinfo	*infos;
	int i;

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

int main(int argc, char **argv)
{
	t_threadinfo *infos;
	int i;
	t_parameters	*parameters;
	parameters = malloc(sizeof(t_parameters));
	init_parameters(parameters);
	set_parameters(parameters, argc, argv);
	t_philosopher	*philosophers[parameters->nb_philosophers];
	pthread_mutex_t *forks[parameters->nb_philosophers];
	pthread_t	threads[parameters->nb_philosophers];
	pthread_t	monitor;

	if (argc > 8)
		return (-1);
	parameters->start_time = current_timestamp();
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