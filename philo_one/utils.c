#include "philo_one.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

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

int	ft_atoi(const char *nptr)
{
	long	num;
	int		digit;
	int		i;

	num = 0;
	i = 0;
	while (nptr[i])
	{
		digit = nptr[i++] - '0';
		num = num * 10 + digit;
	}
	return (num);
}

int	free_memory(t_phil *phils, t_data *args)
{
	int	i;

	if (args->forks)
	{
		i = 0;
		while (i < args->num)
			pthread_mutex_destroy(&args->forks[i++]);
		free(args->forks);
		args->forks = NULL;
	}
	if (args->m_death)
		pthread_mutex_destroy(args->m_death);
	if (phils)
	{
		free(phils);
		phils = NULL;
	}
	return (1);
}

void	set_start_time(t_phil *phil)
{
	int				i;

	i = 0;
	phil->prog_args->sim_start = get_time();
	while (i < phil->prog_args->num)
	{
		phil[i].last_eat = phil->prog_args->sim_start;
		i++;
	}
}
