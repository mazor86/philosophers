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

long	get_time(void)
{
	long			time;
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	time = (long)((cur.tv_sec * 1000000)) + cur.tv_usec;
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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int free_memory(t_phil *phils, t_data *args)
{
	int	i;

	if (args->forks)
	{
		i = 0;
		while (i < args->num)
		{
			pthread_mutex_unlock(&args->forks[i]);
			pthread_mutex_destroy(&args->forks[i++]);
		}
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
