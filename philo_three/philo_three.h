#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# define RESET "\x1B[0m"
# define RED_BOLD "\x1B[1;31m"
# define GREEN "\x1B[32m"
# define CYAN "\x1B[36m"

typedef struct s_data
{
	int				exit;
	int				num;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				count;
	long			sim_start;
	pid_t			*pid;
	sem_t			*sem_left;
	sem_t			*forks;
	sem_t			*sem_print;
	sem_t			*sem_death;
}	t_data;

typedef struct s_phil
{
	int				index;
	long			last_eat;
	int				count_eat;
	t_data			*prog_args;
}	t_phil;

int		ft_atoi(const char *nptr);
int		is_all_digit(char *str);
int		start_program(t_data *args);
void	*check_stop(void *args);
void	*check_stop_eat(void *args);
void	*eating(void *args);
int		free_memory(t_phil *phils, t_data *args);
long	get_time(void);
void	print_message(t_phil *phil, char *message);
void	sleep_function(int time);
void	init_action(void (*action[4])(t_phil *));
void	kill_all(pid_t *pid, int num, pid_t *eat_pid);

#endif