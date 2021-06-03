#include "philo_three.h"

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
	if (args->forks && args->forks != SEM_FAILED)
		sem_close(args->forks);
	if (args->sem_death && args->sem_death != SEM_FAILED)
		sem_close(args->sem_death);
	if (args->sem_left && args->sem_left != SEM_FAILED)
		sem_close(args->sem_left);
	if (args->pid)
		free(args->pid);
	if (phils)
	{
		free(phils);
		phils = NULL;
	}
	return (1);
}
