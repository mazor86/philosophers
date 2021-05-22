#include "philo_one.h"

void	sleep_function(int time)
{
	usleep(time);
}

void	print_message(t_phil *phil, char *message, long cur)
{
	long			time_diff;

	pthread_mutex_lock(phil->prog_args->m_print);
	time_diff = cur - phil->prog_args->sim_start;
	printf("%s%-10ld %s%d%s %s\n", GREEN, time_diff, CYAN,
		phil->index, RESET, message);
	pthread_mutex_unlock(phil->prog_args->m_print);
}

void *eating(void *phil_args)
{
	t_phil	*phil;
	struct timeval	cur;

	phil = (t_phil *)phil_args;
	while (1)
	{
		pthread_mutex_lock(phil->l_fork);
		gettimeofday(&cur, NULL);
		print_message(phil, "has taken a fork", get_time(cur));
		pthread_mutex_lock(phil->r_fork);
		gettimeofday(&cur, NULL);
		phil->last_eat = get_time(cur);
		print_message(phil, "is eating", phil->last_eat);
		sleep_function(phil->prog_args->to_eat);
		pthread_mutex_unlock(phil->l_fork);
		pthread_mutex_unlock(phil->r_fork);
		gettimeofday(&cur, NULL);
		print_message(phil, "is sleeping", get_time(cur));
		sleep_function(phil->prog_args->to_sleep);
		gettimeofday(&cur, NULL);
		print_message(phil, "is thinking", get_time(cur));
	}
}
