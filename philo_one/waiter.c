#include "philo_one.h"

void	*waiter(void *args)
{
	t_phil	*phils;
	int 	i;
	struct timeval	_time;
	long 	cur_time;

	phils = (t_phil *)args;
	while (1)
	{
		i = 0;
		while (i < phils->prog_args->num)
		{
			gettimeofday(&_time, NULL);
			if (phils[i].last_eat + phils->prog_args->to_die < get_time(_time))

			i++;
		}
	}
}