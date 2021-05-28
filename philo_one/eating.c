#include "philo_one.h"

static void	sleep_function(int time)
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

static void	wait_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	pthread_mutex_unlock(mutex);
}

static void	take_fork(t_phil *phil)
{
	pthread_mutex_lock(phil->l_fork);
	pthread_mutex_lock(phil->prog_args->m_print);
	print_message(phil, "has taken a fork");
	pthread_mutex_unlock(phil->prog_args->m_print);
}

static void	start_eat(t_phil *phil)
{
	pthread_mutex_lock(phil->r_fork);
	pthread_mutex_lock(phil->prog_args->m_print);
	print_message(phil, "has taken a fork");
	phil->last_eat = get_time();
	print_message(phil, "is eating");
	pthread_mutex_unlock(phil->prog_args->m_print);
	sleep_function(phil->prog_args->to_eat);
	phil->count_eat++;
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
	if (phil->count_eat == phil->prog_args->count)
		phil->prog_args->phil_left--;
}

void	*eating(void *phil_args)
{
	t_phil	*phil;
	t_data	*args;

	phil = (t_phil *)phil_args;
	args = phil->prog_args;
	if (phil->index % 2)
		sleep_function(50000);
	while (1)
	{
		wait_mutex(args->m_eat);
		take_fork(phil);
		wait_mutex(args->m_eat);
		start_eat(phil);
		pthread_mutex_unlock(args->m_eat);
		pthread_mutex_lock(args->m_print);
		print_message(phil, "is sleeping");
		pthread_mutex_unlock(args->m_print);
		sleep_function(args->to_sleep);
		wait_mutex(args->m_eat);
		pthread_mutex_lock(args->m_print);
		print_message(phil, "is thinking");
		pthread_mutex_unlock(args->m_print);
	}
}
