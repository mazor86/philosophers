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
	usleep(time * 0.5);
	cur = get_time();
	while (cur < end)
	{
		usleep(10);
		cur = get_time();
	}
}

void	kill_all(pid_t *pid, int num, pid_t *eat_pid)
{
	int	i;

	i = 0;
	while (i < num)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	if (eat_pid)
		kill(*eat_pid, SIGKILL);
}
