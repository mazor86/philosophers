#include "philo_three.h"

void	*check_stop_eat(void *args)
{
	int		i;
	t_phil	*phil;

	phil = (t_phil *)args;
	i = 0;
	while (i < phil->prog_args->num)
	{
		sem_wait(phil->prog_args->sem_left);
		i++;
	}
	sem_wait(phil->prog_args->sem_print);
	print_message(phil, "simulation stopped");
	kill_all(phil->prog_args->pid, phil->prog_args->num, NULL);
	return (NULL);
}

void	*check_stop(void *args)
{
	t_phil	*phils;

	phils = (t_phil *)args;
	while (1)
	{
		usleep(10);
		sem_wait(phils->prog_args->sem_print);
		if (phils->last_eat + phils->prog_args->to_die <= get_time())
		{
			sem_wait(phils->prog_args->sem_death);
			phils->prog_args->exit = 1;
			print_message(phils, "died");
			exit(0);
		}
		sem_post(phils->prog_args->sem_print);
	}
}

void	*eating(void *phil_args)
{
	t_phil		*phil;
	int			i;
	void		(*action[4])(t_phil *);
	pthread_t	tid;

	phil = (t_phil *)phil_args;
	init_action(action);
	if (pthread_create(&tid, NULL, check_stop, phil_args))
		exit(1);
	pthread_detach(tid);
	while (1)
	{
		i = 0;
		while (i < 4)
		{
			if (phil->prog_args->exit)
				return (NULL);
			action[i](phil);
			i++;
		}
	}
}
