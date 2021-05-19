#include "philo_one.h"

int 	is_all_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	validate_args(t_data *args, char **av)
{
	args->num = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->times = ft_atoi(av[5]);
	else
		args->times = -1;
	if (args->time_to_die < 60 || args->time_to_eat < 60
		|| args->time_to_sleep < 60)
		return (0);
	if (args->num < 2 || args->num > 200)
		return (0);
	if (!args->times)
		return (0);
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

int	main(int ar, char **av)
{
	t_data	*prog_args;
	int		exit_status;

	prog_args = check_args(ar, av);
	if (prog_args)
	{
		exit_status = start_program(prog_args);
		if (exit_status)
			printf("Run-time ERROR!\n");
		free(prog_args);
	}
	else
	{
		printf("ERROR: Wrong arguments!\n");
		return (1);
	}
	return (exit_status);
}
