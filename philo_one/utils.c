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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		index;
	int		array[11];
	long	number;

	index = 0;
	number = n;
	if (n < 0)
	{
		number *= -1;
		ft_putchar_fd('-', fd);
	}
	while (number != 0)
	{
		array[index] = number % 10;
		number /= 10;
		index++;
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	while (index != 0)
	{
		ft_putchar_fd(array[index - 1] + '0', fd);
		index--;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}