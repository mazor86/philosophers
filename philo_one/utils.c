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

long	get_time(struct timeval cur)
{
	long	time;

	time = (long)((cur.tv_sec * 1000));
	time += (long)(cur.tv_usec) / 1000;
	return (time);
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

int free_memory(t_phil *phils, t_data *args)
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
	if (args->m_print)
		pthread_mutex_destroy(args->m_print);
	if (phils)
	{
		free(phils);
		phils = NULL;
	}
	return (1);
}
