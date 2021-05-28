#include "philo_one.h"

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
			pthread_mutex_lock(phils->prog_args->m_eat);
			if (phils[i].last_eat + phils->prog_args->to_die < get_time()
				|| phils->prog_args->phil_left == 0)
			{
				pthread_mutex_lock(phils->prog_args->m_print);
				if (phils[i].last_eat + phils->prog_args->to_die < get_time())
					print_message(&phils[i], "died");
				else
					print_message(phils, "simulation stopped");
				pthread_mutex_unlock(phils->prog_args->m_death);
				return (NULL);
			}
			pthread_mutex_unlock(phils->prog_args->m_eat);
		}
	}
}
