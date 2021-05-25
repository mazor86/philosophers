#include "philo_one.h"

void	sleep_function(int time)
{
	long	cur;
	long	end;

	end = get_time() + time;
	usleep(time * 0.9);
	cur = get_time();
	while (cur < end)
	{
		usleep(10);
		cur = get_time();
	}
}

void	print_message(t_phil *phil, char *message, long cur)
{
	long			time_diff;

	pthread_mutex_lock(phil->prog_args->m_print);
	time_diff = cur - phil->prog_args->sim_start;
	printf("%s%-10ld %s%d%s %s\n", GREEN, time_diff / 1000, CYAN,
		phil->index, RESET, message);
	pthread_mutex_unlock(phil->prog_args->m_print);
}

void	*eating(void *phil_args)
{
	t_phil			*phil;

	phil = (t_phil *)phil_args;
	if (phil->index % 2)
		sleep_function(50000);
	while (1)
	{
		pthread_mutex_lock(phil->l_fork);
		print_message(phil, "has taken a fork", get_time());
		pthread_mutex_lock(phil->r_fork);
		print_message(phil, "has taken a fork", get_time());
		phil->last_eat = get_time();
		print_message(phil, "is eating", phil->last_eat);
		sleep_function(phil->prog_args->to_eat);
		phil->count_eat++;
		pthread_mutex_unlock(phil->l_fork);
		pthread_mutex_unlock(phil->r_fork);
		print_message(phil, "is sleeping", get_time());
		sleep_function(phil->prog_args->to_sleep);
		print_message(phil, "is thinking", get_time());
	}
}
