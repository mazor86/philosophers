#include "philo_one.h"

void	sleep_function(int time)
{
	usleep(time);
}

long	get_timestamp(t_time cur, t_time start)
{
	long time;

	time = (long)(cur.tv_sec - start.tv_sec) * 1000;
	time += (long)(cur.tv_usec - start.tv_usec) / 1000;
	return (time);
}

void *eating(void *phil_args)
{
	t_phil	*phil;
	t_time	cur;
	long 	time_diff;

	phil = (t_phil *)phil_args;
	phil->last_eat = phil->prog_args->sim_start;
	while (1)
	{
		pthread_mutex_lock(phil->l_fork);
		pthread_mutex_lock(phil->prog_args->m_print);
		gettimeofday(&cur, NULL);
		time_diff = get_timestamp(cur, phil->prog_args->sim_start);
		printf("%-10ld %3d has taken a fork\n", time_diff, phil->index);
		pthread_mutex_unlock(phil->prog_args->m_print);
		pthread_mutex_lock(phil->r_fork);
		pthread_mutex_lock(phil->prog_args->m_print);
		gettimeofday(&phil->last_eat, NULL);
		time_diff = get_timestamp(phil->last_eat, phil->prog_args->sim_start);
		printf("%-10ld %3d is eating\n", time_diff, phil->index);
		pthread_mutex_unlock(phil->prog_args->m_print);
		sleep_function(phil->prog_args->time_to_eat);
		pthread_mutex_unlock(phil->l_fork);
		pthread_mutex_unlock(phil->r_fork);
		pthread_mutex_lock(phil->prog_args->m_print);
		gettimeofday(&cur, NULL);
		time_diff = get_timestamp(cur, phil->prog_args->sim_start);
		printf("%-10ld %3d is sleeping\n", time_diff, phil->index);
		pthread_mutex_unlock(phil->prog_args->m_print);
		sleep_function(phil->prog_args->time_to_sleep);
		pthread_mutex_lock(phil->prog_args->m_print);
		gettimeofday(&cur, NULL);
		time_diff = get_timestamp(cur, phil->prog_args->sim_start);
		printf("%-10ld %3d is thinking\n", time_diff, phil->index);
		pthread_mutex_unlock(phil->prog_args->m_print);
	}
}