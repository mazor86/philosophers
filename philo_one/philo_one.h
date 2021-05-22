#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct timeval t_time;
typedef struct s_data
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times;
	t_time			sim_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*m_print;
}	t_data;

typedef struct s_phil
{
	int				index;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_time			last_eat;
	int				num_eat;
	t_data			*prog_args;
}	t_phil;

//typedef struct s_arg
//{
//	t_phil			*philosophers;
//	pthread_mutex_t	*forks;
//	pthread_mutex_t	*m_print;
//	t_data 			*prog_args;
//	int 			i;
//}	t_arg;

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		start_program(t_data *args);
void 	*eating(void *args);

#endif