#include "philo_two.h"

long	get_time(void)
{
	long			time;
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	time = (long)((cur.tv_sec * 1000000)) + cur.tv_usec;
	return (time);
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
			sem_wait(phils->prog_args->sem_eat);
			if (phils[i].last_eat + phils->prog_args->to_die < get_time()
				|| phils->prog_args->phil_left == 0)
			{
				sem_wait(phils->prog_args->sem_print);
				if (phils[i].last_eat + phils->prog_args->to_die < get_time())
					print_message(&phils[i], "died");
				else
					print_message(phils, "simulation stopped");
				sem_post(phils->prog_args->sem_death);
				return (NULL);
			}
			sem_post(phils->prog_args->sem_eat);
		}
	}
}
