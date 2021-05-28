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
			pthread_mutex_lock(phils->prog_args->m_eat);
			if (phils[i].last_eat + phils->prog_args->to_die < get_time())
			{
				pthread_mutex_lock(phils->prog_args->m_print);
				print_message(&phils[i], "died");
				pthread_mutex_unlock(phils->prog_args->m_death);
				return (NULL);
			}
			if (phils->prog_args->phil_left == 0)
			{
				pthread_mutex_lock(phils->prog_args->m_print);
				print_message(phils, "simulation stopped");
//				time_diff = get_time() - phils->prog_args->sim_start;
//				printf("%s%-10ld %s %s%s\n", GREEN, time_diff / 1000, MAGENTA, "simulation stop", RESET);
				pthread_mutex_unlock(phils->prog_args->m_death);
				return (NULL);
			}
			pthread_mutex_unlock(phils->prog_args->m_eat);
			i++;
		}
	}
}
