#include "philo_one.h"

static int	free_memory(t_arg *func_args, int num_of_phil)
{
	int	i;

	if (func_args->philosophers)
	{
		free(func_args->philosophers);
		func_args->philosophers = NULL;
	}
	if (func_args->forks)
	{
		i = 0;
		while (i < num_of_phil)
			pthread_mutex_destroy(&func_args->forks[i++]);
		free(func_args->forks);
		func_args->forks = NULL;
	}
	if (func_args->m_print)
	{
		pthread_mutex_destroy(func_args->m_print);
		free(func_args->m_print);
	}
	free(func_args);
	func_args = NULL;
	return (1);
}

static t_phil	*init_philosophers(int num_of_phil)
{
	t_phil	*philosophers;
	int		i;

	philosophers = (t_phil *)malloc(sizeof(t_phil) * num_of_phil);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < num_of_phil)
	{
		philosophers[i].index = i + 1;
		philosophers[i].l_fork = (i + 1) % num_of_phil;
		philosophers[i].r_fork = (i + 2) % num_of_phil;
		philosophers[i].num_eat = 0;
		gettimeofday(&philosophers[i].last_eat, NULL);
		i++;
	}
	return (philosophers);
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

static int	init_args(t_arg *func_args, t_data *prog_args)
{
	t_phil			*philosophers;
	pthread_mutex_t	*forks;

	func_args->philosophers = NULL;
	func_args->forks = NULL;
	func_args->m_print = NULL;
	philosophers = init_philosophers(prog_args->num);
	if (!philosophers)
		return (1);
	forks = init_forks(prog_args->num);
	if (!forks)
		return (1);
	func_args->m_print = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!func_args->m_print)
		return (1);
	if (pthread_mutex_init(func_args->m_print, NULL))
		return (1);
	func_args->prog_args = prog_args;
	return (0);
}

int	start_program(t_data *prog_args)
{
	t_arg		*func_args;
	pthread_t	*ph_treads;
	int			start_status;
	int 		i;

	func_args = (t_arg *)malloc(sizeof(t_arg));
	if (!func_args)
		return (1);
	start_status = init_args(func_args, prog_args);
	if (start_status)
		return (free_memory(func_args, prog_args->num));
	ph_treads = (pthread_t *) malloc(sizeof(ph_treads) * prog_args->num);
	if (!ph_treads)
		return (free_memory(func_args, prog_args->num));
	i = 0;
	while (i < prog_args->num)
	{

		pthread_create(&ph_treads[i], NULL, eating, (void *)func_args);
	}
	return (0);
}
//TODO переделать передаваемые в потоки аргументы. нужно, чтобы в поток уходили данные
// конкретного философа + указатель на мьютексы и другие данные