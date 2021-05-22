#include "philo_one.h"

static int free_memory(t_phil *phils, t_data *args)
{
	int	i;

	if (args->forks)
	{
		i = 0;
		while (i < args->num)
			pthread_mutex_destroy(&args->forks[i++]);
		free(args->forks);
		args->forks = NULL;
	}
	if (args->m_print)
	{
		pthread_mutex_destroy(args->m_print);
		free(args->m_print);
	}
	free(phils);
	phils = NULL;
	return (1);
}

static void	init_philosophers(t_phil *philosophers, t_data *prog_args)
{
	int		i;

	i = 0;
	while (i < prog_args->num)
	{
		philosophers[i].index = i + 1;
		philosophers[i].l_fork = &prog_args->forks[i % prog_args->num];
		philosophers[i].r_fork = &prog_args->forks[(i + 1) % prog_args->num];
		philosophers[i].num_eat = 0;
		philosophers[i].prog_args = prog_args;
//		philosophers[i].last_eat, NULL);
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

static int init_args(t_phil *phils, t_data *prog_args)
{
	prog_args->forks = NULL;
	prog_args->m_print = NULL;
	prog_args->forks = init_forks(prog_args->num);
	if (!prog_args->forks)
		return (1);
	init_philosophers(phils, prog_args);
	prog_args->m_print = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!prog_args->m_print)
		return (1);
	if (pthread_mutex_init(prog_args->m_print, NULL))
		return (1);
	return (0);
}

//int	start_program(t_data *prog_args)
//{
//	t_arg		*func_args;
//	pthread_t	*ph_treads;
//	int			start_status;
//	int 		i;
//
//	func_args = (t_arg *)malloc(sizeof(t_arg));
//	if (!func_args)
//		return (1);
//	start_status = init_args(func_args, prog_args);
//	if (start_status)
//		return (free_memory(func_args, prog_args->num));
//	ph_treads = (pthread_t *) malloc(sizeof(ph_treads) * prog_args->num);
//	if (!ph_treads)
//		return (free_memory(func_args, prog_args->num));
//	i = 0;
//	while (i < prog_args->num)
//	{
//
//		pthread_create(&ph_treads[i], NULL, eating, (void *)func_args);
//	}
//	return (0);
//}
//TODO переделать передаваемые в потоки аргументы. нужно, чтобы в поток уходили данные
// конкретного философа + указатель на мьютексы и другие данные

int	start_program(t_data *prog_args)
{
	t_phil		*philosophers;
	int 		start_status;
	pthread_t	*ph_treads;
	int 		i;

	philosophers = (t_phil *)malloc(sizeof(t_phil) * prog_args->num);
	if (!philosophers)
		return (1);
	start_status = init_args(philosophers, prog_args);
	if (start_status)
		return (free_memory(philosophers, prog_args));
	ph_treads = (pthread_t *) malloc(sizeof(ph_treads) * prog_args->num);
	if (!ph_treads)
		return (free_memory(philosophers, prog_args));
	i = 0;
	gettimeofday(&prog_args->sim_start, NULL);

	while (i < prog_args->num)
	{
		pthread_create(&ph_treads[i], NULL, eating, (void *)&philosophers[i]);
		i++;
	}
	while (1)
	{

	}
	return (0);
}