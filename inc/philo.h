/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:23:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/11 16:42:39 by lsordo           ###   ########.fr       */
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
# define THINKING	0b001
# define EATING		0b010
# define SLEEPING	0b100

/* threads and mutexes missing in the structures yet */
typedef struct s_data
{
	int				n_philo;
	useconds_t		clock;
	useconds_t		t_die;
	useconds_t		t_eat;
	useconds_t		t_sleep;
	int				n_lunch;
	struct s_philo	**philo;
	pthread_mutex_t	**forks;
}					t_data;

typedef struct s_philo
{
	int			id;
	int			shift;
	int			doing;
	int			lfork;
	int			rfork;
	int			forks;
	pthread_t	thread;
	t_data		*data;
	useconds_t	lapsed_lunch;
}				t_philo;

void	data_init(t_data *data, char **argv);
void	data_cleanup(t_data *data);
void	mutex_init(t_data *data);
void	mutex_destroy(t_data *data);
int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	tmp_prtarray(char **arr);
void	tmp_prtdata(t_data	*data);

#endif
