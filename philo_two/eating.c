#include "philo_two.h"

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

static void	wait_mutex(sem_t *mutex)
{
	sem_wait(mutex);
	sem_post(mutex);
}

static void	take_fork(t_phil *phil)
{
	sem_wait(phil->prog_args->forks);
	sem_wait(phil->prog_args->sem_print);
	print_message(phil, "has taken a fork");
	sem_post(phil->prog_args->sem_print);
}

static void	start_eat(t_phil *phil)
{
	sem_wait(phil->prog_args->forks);
	sem_post(phil->prog_args->sem_eat);
	sem_wait(phil->prog_args->sem_print);
	print_message(phil, "has taken a fork");
	phil->last_eat = get_time();
	print_message(phil, "is eating");
	sem_post(phil->prog_args->sem_print);
	sleep_function(phil->prog_args->to_eat);
	phil->count_eat++;
	sem_post(phil->prog_args->forks);
	sem_post(phil->prog_args->forks);
	if (phil->count_eat == phil->prog_args->count)
		phil->prog_args->phil_left--;
}

void	*eating(void *phil_args)
{
	t_phil	*phil;
	t_data	*args;

	phil = (t_phil *)phil_args;
	args = phil->prog_args;
	while (1)
	{
		sem_wait(args->sem_eat);
		take_fork(phil);
		start_eat(phil);
		wait_mutex(args->sem_eat);
		sem_wait(args->sem_print);
		print_message(phil, "is sleeping");
		sem_post(args->sem_print);
		sleep_function(args->to_sleep);
		wait_mutex(args->sem_eat);
		sem_wait(args->sem_print);
		print_message(phil, "is thinking");
		sem_post(args->sem_print);
	}
}
