#include "philo_two.h"

static void	init_philosophers(t_phil *philosophers, t_data *prog_args)
{
	int		i;

	i = 0;
	while (i < prog_args->num)
	{
		philosophers[i].index = i + 1;
		philosophers[i].count_eat = 0;
		philosophers[i].prog_args = prog_args;
		i++;
	}
}

static sem_t	*init_forks(int num_of_phil)
{
	sem_t	*forks;

	forks = sem_open("sem_forks", O_CREAT, 0644, num_of_phil);
	if (forks == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_forks");
	return (forks);
}

static int	init_semaphors(t_data *prog_args)
{
	prog_args->sem_print = sem_open("sem_print", O_CREAT, 0644, 1);
	if (prog_args->sem_print == SEM_FAILED)
		return (0);
	sem_unlink("sem_print");
	prog_args->sem_death = sem_open("sem_death", O_CREAT, 0644, 0);
	if (prog_args->sem_death == SEM_FAILED)
		return (0);
	sem_unlink("sem_death");
	return (1);
}

static t_phil	*init_args(t_data *prog_args)
{
	t_phil	*phils;

	prog_args->forks = init_forks(prog_args->num);
	if (!prog_args->forks)
		return (NULL);
	if (!init_semaphors(prog_args))
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
		usleep(100);
		i++;
	}
	i = 0;
	while (i < prog_args->num)
		pthread_join(ph_threads[i++], NULL);
	sem_wait(prog_args->sem_death);
	usleep(100000);
	free(ph_threads);
	return (free_memory(philosophers, prog_args) - 1);
}
