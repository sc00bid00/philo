/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:19:35 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/14 11:51:50 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (num < 0 && sign < 0)
			return (0);
		if (num < 0 && sign > 0)
			return (-1);
		num = 10 * num + *str - '0';
		str++;
	}
	return (sign * num);
}

unsigned long	ft_clock(unsigned long t_start)
{
	struct timeval	ti;
	int				t;

	gettimeofday(&ti, NULL);
	t = ti.tv_sec * 1000 + ti.tv_usec / 1000;
	return (t - t_start);
}

void	ft_wait(unsigned long t)
{
	unsigned long now;

	now = ft_clock(0);
	while (ft_clock(0) - now < t)
		usleep(T_SLOT);
}

void	ft_print(t_philo *p, char *msg)
{
	int	var;

	pthread_mutex_lock(&p->data->p_lock);
	pthread_mutex_lock(&p->data->lock);
	var = p->data->stop;
	pthread_mutex_unlock(&p->data->lock);
	if (!var)
		printf("%lu %d %s\n", ft_clock(p->data->t_start), p->id, msg);
	pthread_mutex_unlock(&p->data->p_lock);
}
