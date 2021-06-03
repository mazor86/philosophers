#include "philo_three.h"

static void	take_fork(t_phil *phil)
{
	sem_wait(phil->prog_args->forks);
	sem_wait(phil->prog_args->sem_print);
	if (!phil->prog_args->exit)
		print_message(phil, "has taken a fork");
	sem_post(phil->prog_args->sem_print);
}

static void	start_eat(t_phil *phil)
{
	sem_wait(phil->prog_args->sem_death);
	sem_post(phil->prog_args->sem_death);
	sem_wait(phil->prog_args->forks);
	sem_wait(phil->prog_args->sem_print);
	if (!phil->prog_args->exit)
		print_message(phil, "has taken a fork");
	phil->last_eat = get_time();
	if (!phil->prog_args->exit)
		print_message(phil, "is eating");
	sem_post(phil->prog_args->sem_print);
	sleep_function(phil->prog_args->to_eat);
	phil->count_eat++;
	sem_post(phil->prog_args->forks);
	sem_post(phil->prog_args->forks);
	if (phil->count_eat == phil->prog_args->count)
		sem_post(phil->prog_args->sem_left);
}

static void	sleeping(t_phil *phil)
{
	sem_wait(phil->prog_args->sem_print);
	if (!phil->prog_args->exit)
		print_message(phil, "is sleeping");
	sem_post(phil->prog_args->sem_print);
	sleep_function(phil->prog_args->to_sleep);
}

static void	think(t_phil *phil)
{
	sem_wait(phil->prog_args->sem_print);
	if (!phil->prog_args->exit)
		print_message(phil, "is think");
	sem_post(phil->prog_args->sem_print);
}

void	init_action(void (*action[4])(t_phil *))
{
	action[0] = take_fork;
	action[1] = start_eat;
	action[2] = sleeping;
	action[3] = think;
}
