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

void	print_message(t_phil *phil, char *message)
{
	long	cur;
	long	time_diff;

	pthread_mutex_lock(phil->prog_args->m_print);
	cur = get_time();
	if (!ft_strcmp(message, "is eating"))
		phil->last_eat = cur;
	time_diff = cur - phil->prog_args->sim_start;
	ft_putstr_fd(GREEN, 1);
	ft_putnbr_fd(time_diff / 1000, 1);
	ft_putstr_fd(RESET, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(CYAN, 1);
	ft_putnbr_fd(phil->index, 1);
	ft_putstr_fd(RESET, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
//	printf("%s%-10ld %s%d%s %s\n", GREEN, time_diff / 1000, CYAN,
//		phil->index, RESET, message);
	pthread_mutex_unlock(phil->prog_args->m_print);
}

static void	take_fork(t_phil *phil)
{

	pthread_mutex_lock(phil->l_fork);
	print_message(phil, "has taken a fork");
}

static void	start_eat(t_phil *phil)
{

	pthread_mutex_lock(phil->r_fork);
	print_message(phil, "has taken a fork");
	phil->last_eat = get_time();
	print_message(phil, "is eating");
	sleep_function(phil->prog_args->to_eat);
	phil->count_eat++;
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
	if (phil->count_eat == phil->prog_args->count)
		phil->prog_args->phil_left--;
}

void	*eating(void *phil_args)
{
	t_phil			*phil;

	phil = (t_phil *)phil_args;
	if (phil->index % 2)
		sleep_function(50000);
	while (1)
	{
		if (pthread_mutex_lock(phil->prog_args->m_eat))
		{
			write(1, "AHTUNG\n", 7);
			return (NULL);
		};
		pthread_mutex_unlock(phil->prog_args->m_eat);
		take_fork(phil);
		if (pthread_mutex_lock(phil->prog_args->m_eat))
		{
			write(1, "AHTUNG\n", 7);
			return (NULL);
		};
		pthread_mutex_unlock(phil->prog_args->m_eat);
		start_eat(phil);
		if (pthread_mutex_lock(phil->prog_args->m_eat))
		{
			write(1, "AHTUNG\n", 7);
			return (NULL);
		};
		pthread_mutex_unlock(phil->prog_args->m_eat);
		print_message(phil, "is sleeping");
		sleep_function(phil->prog_args->to_sleep);
		if (pthread_mutex_lock(phil->prog_args->m_eat))
		{
			write(1, "AHTUNG\n", 7);
			return (NULL);
		};
		pthread_mutex_unlock(phil->prog_args->m_eat);
		print_message(phil, "is thinking");
	}
}
