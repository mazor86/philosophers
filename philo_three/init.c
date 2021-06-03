#include "philo_three.h"

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
	prog_args->sem_left = sem_open("sem_left", O_CREAT, 0644, 0);
	if (prog_args->sem_left == SEM_FAILED)
		return (0);
	sem_unlink("sem_left");
	return (1);
}

static t_phil	*init_args(t_data *prog_args, pid_t *pid)
{
	t_phil	*phils;

	prog_args->forks = sem_open("sem_forks", O_CREAT, 0644, prog_args->num);
	if (prog_args->forks == SEM_FAILED)
		return (NULL);
	sem_unlink("sem_forks");
	if (!init_semaphors(prog_args))
		return (NULL);
	phils = (t_phil *)malloc(sizeof(t_phil));
	if (!phils)
		return (NULL);
	prog_args->sim_start = get_time();
	prog_args->pid = pid;
	phils->last_eat = prog_args->sim_start;
	phils->count_eat = 0;
	phils->prog_args = prog_args;
	return (phils);
}

static void	run_processes(t_phil *phil)
{
	int	i;

	i = 0;
	while (i < phil->prog_args->num)
	{
		phil->prog_args->pid[i] = fork();
		if (phil->prog_args->pid[i] < 0)
			exit(1);
		else if (phil->prog_args->pid[i] == 0)
		{
			phil->index = i + 1;
			eating((void *)phil);
			exit(0);
		}
		usleep(50);
		i++;
	}
}

int	start_program(t_data *prog_args)
{
	t_phil		*phils;
	pid_t		*pid;
	pid_t		eat_pid;
	int			status;

	phils = NULL;
	pid = (pid_t *)malloc(sizeof(pid_t) * prog_args->num);
	if (!pid)
		return (free_memory(phils, prog_args));
	phils = init_args(prog_args, pid);
	if (!phils)
		return (free_memory(phils, prog_args));
	run_processes(phils);
	eat_pid = fork();
	if (eat_pid < 0)
		exit(1);
	else if (eat_pid == 0)
	{
		check_stop_eat((void *)phils);
		exit(0);
	}
	waitpid(-1, &status, 0);
	kill_all(pid, prog_args->num, &eat_pid);
	return (free_memory(phils, prog_args) - 1);
}
