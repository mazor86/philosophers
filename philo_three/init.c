#include "philo_three.h"

//static void	init_philosophers(t_phil *philosophers, t_data *prog_args)
//{
//	int		i;
//
//	i = 0;
//	while (i < prog_args->num)
//	{
//		philosophers[i].index = i + 1;
//		philosophers[i].count_eat = 0;
//		philosophers[i].prog_args = prog_args;
//		i++;
//	}
//}

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
	prog_args->sem_death = sem_open("sem_death", O_CREAT, 0644, 1);
	if (prog_args->sem_death == SEM_FAILED)
		return (0);
	sem_unlink("sem_death");
	prog_args->sem_left = sem_open("sem_left", O_CREAT, 0644, prog_args->num);
	if (prog_args->sem_left == SEM_FAILED)
		return (0);
	sem_unlink("sem_left");
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
	phils = (t_phil *)malloc(sizeof(t_phil));
	if (!phils)
		return (NULL);
	phils->count_eat = 0;
	phils->prog_args = prog_args;
//	init_philosophers(phils, prog_args);
	return (phils);
}

void	kill_all(pid_t *pid, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}

int	start_program(t_data *prog_args)
{
	t_phil		*philosophers;
	pid_t		*pid;
	int			i;
//	pthread_t	*ph_threads;
//	pthread_t	thread;
	int			status;

	philosophers = init_args(prog_args);
	if (!philosophers)
		return (free_memory(philosophers, prog_args));
	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * prog_args->num);
	if (!pid)
		return (free_memory(philosophers, prog_args));
//	set_start_time(philosophers);
	prog_args->sim_start = get_time();
	philosophers->last_eat = prog_args->sim_start;
	while (i < prog_args->num)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit(1);
		else if (pid[i] == 0)
		{
			philosophers->index = i + 1;
			eating((void *)philosophers);
			exit(0);
		}
		usleep(50);
		i++;
	}
	waitpid(-1, &status, 0);
	kill_all(pid, prog_args->num);
//	ph_threads = (pt _memory(philosophers, prog_args));
//	if (create_and_join(philosophers, &thread, ph_threads))
//		return (free_memory(philosophers, prog_args));
//	free(ph_threads);
	return (free_memory(philosophers, prog_args) - 1);
}
