#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>

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

long long   current_timestamp(void);
int         ft_atoi(const char *str);
int         eating(t_philosopher *philos, pthread_mutex_t **forks, t_parameters *params);
void	    thinking(t_philosopher *philosopher, t_parameters *parameters);
void	    sleeping(t_philosopher *philosopher, t_parameters *parameters);
void	    init_parameters(t_parameters *parameters);
void	    init_philosopher(t_philosopher *philosopher);
void	    set_parameters(t_parameters *parameters, int argc, char **argv);
void	    *check_death_meals(void *ptr);
bool	    is_starved_to_death(t_philosopher *philo, t_parameters *params);
int	        check_meals(t_philosopher **philosophers, t_parameters *parameters);
bool	    is_someone_dead(t_philosopher **philosophers, int nb_philosophers);
int			create_philos(t_parameters *parameters, pthread_mutex_t **forks, t_philosopher **philosophers);
void		*thread_main(void *ptr);
int   		thread_main_create(t_threadinfo	infos, pthread_t *threads);
void		free_all(t_parameters *params, t_threadinfo infos);
int			check_arg(char **argv);

#endif
