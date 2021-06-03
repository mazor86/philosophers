#include "philo_two.h"

static void	post_semaphors(t_data *args)
{
	sem_post(args->sem_death);
	sem_post(args->sem_print);
}

void	*check_stop(void *args)
{
	t_phil	*phils;
	int		i;

	phils = (t_phil *)args;
	while (1)
	{
		i = -1;
		while (++i < phils->prog_args->num)
		{
			sem_wait(phils->prog_args->sem_print);
			if (phils[i].last_eat + phils->prog_args->to_die < get_time()
				|| phils->prog_args->phil_left == 0)
			{
				sem_wait(phils->prog_args->sem_death);
				phils->prog_args->exit = 1;
				if (phils[i].last_eat + phils->prog_args->to_die < get_time())
					print_message(&phils[i], "died");
				else
					print_message(phils, "simulation stopped");
				post_semaphors(phils->prog_args);
				return (NULL);
			}
			sem_post(phils->prog_args->sem_print);
		}
	}
}

void	*eating(void *phil_args)
{
	t_phil	*phil;
	int		i;
	void	(*action[4])(t_phil *);

	phil = (t_phil *)phil_args;
	if (phil->index % 2)
		sleep_function(50000);
	init_action(action);
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
