#include "philo_three.h"

long	get_time(void)
{
	long			time;
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	time = (long)((cur.tv_sec * 1000)) + cur.tv_usec / 1000;
	return (time);
}

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

int	create_and_join(t_phil *phils, pthread_t *thread, pthread_t *ph_threads)
{
	int	i;

	i = 0;
	set_start_time(phils);
	if (pthread_create(thread, NULL, check_stop, (void *)phils))
		return (1);
	if (pthread_detach(*thread))
		return (1);
	while (i < phils->prog_args->num)
	{
		if (pthread_create(&ph_threads[i], NULL, eating, (void *)&phils[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < phils->prog_args->num)
	{
		if (pthread_join(ph_threads[i++], NULL))
			return (1);
	}
	return (0);
}
