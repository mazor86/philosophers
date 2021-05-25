#include "philo_one.h"

void	*check_stop(void *args)
{
	t_phil	*phils;
	int 	i;
	long	time_diff;

	phils = (t_phil *)args;
	while (1)
	{
		i = 0;
		while (i < phils->prog_args->num)
		{
			if (phils[i].last_eat + phils->prog_args->to_die < get_time())
			{
				pthread_mutex_lock(phils->prog_args->m_print);
				time_diff = get_time() - phils->prog_args->sim_start;
				printf("%s%-10ld %s%d%s %s%s\n", GREEN, time_diff / 1000, CYAN,
					   phils[i].index, MAGENTA, "died", RESET);
				pthread_mutex_unlock(phils->prog_args->m_death);
				return (NULL);
			}
			i++;
		}
	}
}

