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

static int	init_mutex(t_data *prog_args)
{
	prog_args->m_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!prog_args->m_print)
		return (0);
	if (pthread_mutex_init(prog_args->m_print, NULL))
		return (0);
	prog_args->m_death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!prog_args->m_death)
		return (0);
	if (pthread_mutex_init(prog_args->m_death, NULL))
		return (0);
	pthread_mutex_lock(prog_args->m_death);
	prog_args->m_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!prog_args->m_eat)
		return (0);
	if (pthread_mutex_init(prog_args->m_eat, NULL))
		return (0);
	return (1);
}

static t_phil	*init_args(t_data *prog_args)
{
	t_phil	*phils;

	prog_args->forks = init_forks(prog_args->num);
	if (!prog_args->forks)
		return (NULL);
	if (!init_mutex(prog_args))
		return (NULL);
	phils = (t_phil *)malloc(sizeof(t_phil) * prog_args->num);
	if (!phils)
		return (NULL);
	init_philosophers(phils, prog_args);
	return (phils);
}

int	start_program(t_data *prog_args)
{
	t_phil		*philosophers;
	pthread_t	*ph_threads;
	pthread_t	thread;
	int			i;

	philosophers = init_args(prog_args);
	if (!philosophers)
		return (free_memory(philosophers, prog_args));
	ph_threads = (pthread_t *) malloc(sizeof(ph_threads) * prog_args->num);
	if (!ph_threads)
		return (free_memory(philosophers, prog_args));
	i = 0;
	set_start_time(philosophers);
	pthread_create(&thread, NULL, check_stop, (void *)philosophers);
	pthread_detach(thread);
	while (i < prog_args->num)
	{
		pthread_create(&ph_threads[i], NULL, eating, (void *)&philosophers[i]);
		pthread_detach(ph_threads[i]);
		i++;
	}
	pthread_mutex_lock(prog_args->m_death);
	free(ph_threads);
	return (free_memory(philosophers, prog_args) - 1);
}
