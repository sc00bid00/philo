/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:19:35 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/12 17:53:18 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int		ft_atoi(const char *str)
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

int		ft_clock(unsigned long t_start)
{
	struct timeval	ti;
	int				t;

	gettimeofday(&ti, NULL);
	t = ti.tv_sec * 1000 + ti.tv_usec / 1000;
	return (t - t_start);
}

void	ft_wait(int t)
{
	t = t * 1000;
	while (t > T_SLOT)
	{
		usleep(T_SLOT);
		t -= T_SLOT;
	}
	if (t > 0)
		usleep(t);
}

void	ft_print(int t, int id, char *msg)
{
	printf("%d\t%d\t%s\n", t, id, msg);
}
