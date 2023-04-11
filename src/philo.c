/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:23:07 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 16:47:53 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_wait(useconds_t	t)
{
	while ((double)t * 2  > 1)
	{
		usleep(500);
		t -= (double)(500 / 1000);
	}
	usleep(t);
}

useconds_t	putmsg(int id, char *msg)
{
	struct timeval	ti;
	useconds_t		t;

	gettimeofday(&ti, NULL);
	t = 1000 * ti.tv_sec + ti.tv_usec / 1000;
	ft_putnbr_fd(t, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(id, 1);
	ft_putstr_fd(" is ", 1);
	ft_putendl_fd(msg, 1);
	return (t);
}

void	*routine(void *p)
{
	t_philo		*philo;
	useconds_t	t;


	philo = (t_philo *)p;
	if (philo->doing & EATING)
	{
		if (!pthread_mutex_lock(philo->data->forks[philo->lfork]))
			putmsg(philo->id, "took a fork");
		if (!pthread_mutex_lock(philo->data->forks[philo->rfork]))
			t = putmsg(philo->id, "took a fork");
		philo->lapsed_lunch = t;
		putmsg(philo->id, "eating");
		ft_wait(philo->data->t_eat);
		pthread_mutex_unlock(philo->data->forks[philo->rfork]);
		pthread_mutex_unlock(philo->data->forks[philo->lfork]);
		philo->doing = philo->doing<< 1;
	}
	else if (philo->doing & SLEEPING)
	{
		putmsg(philo->id, "sleeping");
		ft_wait(philo->data->t_sleep);
		philo->doing = philo->doing<< 1;
	}
	else if (philo->doing & THINKING)
	{
		putmsg(philo->id, "thinking");
		philo->doing = philo->doing<< 1;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (argc > 7 || argc < 6)
	{
		printf("Wrong arguments - usage:\nnumber_of_philosophers\n\
time_to_die   [ms]\ntime_to_eat   [ms]\ntime_to_sleep [ms]\n\
[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data_init(data, argv);
	mutex_init(data);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create((void *)&data->philo[i]->thread, NULL, &routine, (void *)data->philo[i]);
		i++;
	}
	mutex_destroy(data);
	data_cleanup(data);
	return (0);
}
