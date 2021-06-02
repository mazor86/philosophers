#include "philo_two.h"

int	validate_args(t_data *args, char **av)
{
	args->num = ft_atoi(av[1]);
	args->to_die = ft_atoi(av[2]);
	args->to_eat = ft_atoi(av[3]);
	args->to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->count = ft_atoi(av[5]);
	else
		args->count = -1;
	if (args->to_die < 60 || args->to_eat < 60
		|| args->to_sleep < 60)
		return (0);
	if (args->num < 2 || args->num > 200)
		return (0);
	if (!args->count)
		return (0);
	args->to_die *= 1000;
	args->to_eat *= 1000;
	args->to_sleep *= 1000;
	return (1);
}

static t_data 	*check_args(int ar, char **av)
{
	int		i;
	t_data	*temp;

	if (ar < 5 || ar > 6)
		return (NULL);
	i = 1;
	while (i < ar)
	{
		if (!is_all_digit(av[i++]))
			return (NULL);
	}
	temp = (t_data *)malloc(sizeof(t_data));
	if (!temp)
		return (NULL);
	if (!validate_args(temp, av))
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

static void	init_ptr(t_data *prog_args)
{
	prog_args->forks = NULL;
	prog_args->sem_print = NULL;
	prog_args->sem_death = NULL;
	prog_args->phil_left = prog_args->num;
	prog_args->exit = 0;
}

int	main(int ar, char **av)
{
	t_data	*prog_args;
	int		exit_status;

	prog_args = check_args(ar, av);
	if (prog_args)
	{
		init_ptr(prog_args);
		exit_status = start_program(prog_args);
		if (exit_status)
			printf("%sRun-time ERROR!%s\n", RED_BOLD, RESET);
		usleep(10000);
		sem_close(prog_args->sem_print);
		sem_close(prog_args->sem_death);
		free(prog_args);
	}
	else
	{
		printf("%sERROR: Wrong arguments!%s\n", RED_BOLD, RESET);
		return (1);
	}
	return (exit_status);
}
