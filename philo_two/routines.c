#include "philo_two.h"

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
				phils->prog_args->exit = 1;
				if (phils[i].last_eat + phils->prog_args->to_die < get_time())
					print_message(&phils[i], "died");
				else
					print_message(phils, "simulation stopped");
				sem_post(phils->prog_args->sem_print);
				sem_post(phils->prog_args->sem_death);
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
	init_action(action);
	while (1)
	{
		i = 0;
		while (i < 4)
		{
			if (phil->prog_args->exit)
				return (NULL);
			action[i++](phil);
		}
	}
}
