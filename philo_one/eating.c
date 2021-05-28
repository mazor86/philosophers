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

void	phil_itoa(long n, char *number)
{
	size_t	len;
	long	digit;

	memset(number, 0, 16);
	len = 1;
	digit = n;
	while ((digit /= 10))
		len++;
	digit = n;
	while (digit > 9)
	{
		number[--len] = digit % 10 + '0';
		digit /= 10;
	}
	number[--len] = digit + '0';
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t dst_len;
	size_t src_len;

	if (src && dst)
	{
		dst_len = (size - 1);
		src_len = ft_strlen(src);
		if (size)
		{
			while (*src && dst_len--)
			{
				*dst++ = *src++;
			}
			*dst = '\0';
		}
		return ((src_len));
	}
	return (0);
}
void	print_message(t_phil *phil, char *message)
{
	long	cur;
	char	output[256];
	char	number[16];
	int		i;

	memset(output, 0, 256);
	i = 0;
	memset(number, 0, 16);
	i += ft_strlcpy(output, GREEN, ft_strlen(GREEN) + 1);
	cur = get_time();
	if (!ft_strcmp(message, "is eating"))
		phil->last_eat = cur;
	phil_itoa((cur - phil->prog_args->sim_start) / 1000, number);
	i += ft_strlcpy(output + i, number, ft_strlen(number) + 1);
	output[i++] = ' ';
	i += ft_strlcpy(output + i, CYAN, ft_strlen(CYAN) + 1);
	phil_itoa(phil->index, number);
	i += ft_strlcpy(output + i, number, ft_strlen(number) + 1);
	i += ft_strlcpy(output + i, RESET, ft_strlen(RESET) + 1);
	output[i++] = ' ';
	i += ft_strlcpy(output + i, message, ft_strlen(message) + 1);
	output[i] = '\n';
	pthread_mutex_lock(phil->prog_args->m_print);
	write(1, output, ft_strlen(output));

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
