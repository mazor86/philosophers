#include "philo_one.h"

static void	init_philosophers(t_phil *philosophers, t_data *prog_args)
{
	int		i;

	i = 0;
	while (i < prog_args->num)
	{
		philosophers[i].index = i + 1;
		philosophers[i].l_fork = &prog_args->forks[i % prog_args->num];
		philosophers[i].r_fork = &prog_args->forks[(i + 1) % prog_args->num];
		philosophers[i].count_eat = 0;
		philosophers[i].prog_args = prog_args;
		i++;
	}
}

static pthread_mutex_t	*init_forks(int num_of_phil)
{
	pthread_mutex_t	*forks;
	int				i;
	int				fail;

	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * num_of_phil);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < num_of_phil)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			fail = 0;
			while (fail < i)
				pthread_mutex_destroy(&forks[fail++]);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static t_phil *init_args(t_data *prog_args)
{
	t_phil *phils;

	prog_args->forks = NULL;
	prog_args->m_print = NULL;
	prog_args->forks = init_forks(prog_args->num);
	if (!prog_args->forks)
		return (NULL);
	prog_args->m_print = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!prog_args->m_print)
		return (NULL);
	if (pthread_mutex_init(prog_args->m_print, NULL))
		return (NULL);
	phils = (t_phil *)malloc(sizeof(t_phil) * prog_args->num);
	if (!phils)
		return (NULL);
	init_philosophers(phils, prog_args);
	return (phils);
}

void	set_start_time(t_phil *phil)
{
	int				i;
	struct timeval	sim_start;

	i = 0;
	gettimeofday(&sim_start, NULL);
	phil->prog_args->sim_start = get_time(sim_start);
	while (i < phil->prog_args->num)
	{
		phil[i].last_eat = phil->prog_args->sim_start;
		i++;
	}
}

int	start_program(t_data *prog_args)
{
	t_phil		*philosophers;
	pthread_t	*ph_treads;
	pthread_t	*w_tread;
	int 		i;

	philosophers = init_args(prog_args);
	if (!philosophers)
		return (free_memory(philosophers, prog_args));
	ph_treads = (pthread_t *) malloc(sizeof(ph_treads) * prog_args->num);
	if (!ph_treads)
		return (free_memory(philosophers, prog_args));
	i = 0;
	set_start_time(philosophers);
	while (i < prog_args->num)
	{
		pthread_create(&ph_treads[i], NULL, eating, (void *)&philosophers[i]);
		pthread_detach(ph_treads[i++]);
	}
	return (free_memory(philosophers, prog_args) - 1);
}