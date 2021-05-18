#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int	num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times;
}				t_data;

int		ft_isdigit(int c);
int 	ft_atoi(const char *nptr);
void 	start_program(t_data *args);

#endif