#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define RESET "\x1B[0m"
# define RED_BOLD "\x1B[1;31m"
# define GREEN "\x1B[32m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"

typedef struct s_data
{
	int				num;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				count;
	int				phil_left;
	long			sim_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*m_print;
	pthread_mutex_t	*m_death;
	pthread_mutex_t	*m_eat;
}	t_data;

typedef struct s_phil
{
	int				index;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			last_eat;
	int				count_eat;
	t_data			*prog_args;
}	t_phil;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *nptr);
int		is_all_digit(char *str);
int		start_program(t_data *args);
void	*check_stop(void *args);
void	*eating(void *args);
int		free_memory(t_phil *phils, t_data *args);
long	get_time(void);
void	print_message(t_phil *phil, char *message);
void	set_start_time(t_phil *phil);
void		ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif