/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:23:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 13:17:29 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <philo.h>

# define DEAD		0b000
# define EATING		0b001
# define SLEEPING	0b010
# define THINKING	0b100
# define NO_FORKS	0b00;
# define FORK_RIGHT	0b01;
# define FORK_LEFT	0b10;
# define BOTH_FORKS	0b11;

/* threads and mutexes missing in the structures yet */
typedef struct s_fork
{
	int				id;
	int				state;
	pthread_mutex_t	mutex_fork;
}		t_fork;

typedef struct s_philo
{
	int		id;
	int		shift;
	int		state;
	double	lapsed_lunch;
	t_fork	l_fork;
	t_fork	r_fork;
}			t_philo;

typedef struct s_data
{
	int			n_philo;
	useconds_t	t_die;
	useconds_t	t_eat;
	useconds_t	t_sleep;
	int			n_lunch;
	t_fork		**fork;
	t_philo		**philo;
}			t_data;

void	forks_init(t_data *data);
void	forks_destroy(t_data *data);
void	data_init(t_data *data, char **argv);
int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	tmp_prtarray(char **arr);
void	tmp_prtdata(t_data	*data);



#endif
