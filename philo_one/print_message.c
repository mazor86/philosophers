#include "philo_one.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	phil_itoa(long n, char *number)
{
	size_t	len;
	long	digit;

	memset(number, 0, 16);
	len = 1;
	digit = n;
	while (digit /10)
	{
		digit /= 10;
		len++;
	}
	digit = n;
	while (digit > 9)
	{
		number[--len] = digit % 10 + '0';
		digit /= 10;
	}
	number[--len] = digit + '0';
	while (number[len])
		len++;
	while (len < 6)
		number[len++] = ' ';
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

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
	if (!ft_strcmp(message, "simulation stopped"))
		memset(number, 0, 16);
	i += ft_strlcpy(output + i, number, ft_strlen(number) + 1);
	i += ft_strlcpy(output + i, RESET, ft_strlen(RESET) + 1);
	output[i++] = ' ';
	i += ft_strlcpy(output + i, message, ft_strlen(message) + 1);
	output[i] = '\n';
	write(1, output, ft_strlen(output));
}
