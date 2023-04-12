/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:23:55 by lsordo            #+#    #+#             */
/*   Updated: 2023/04/12 19:26:58 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_ARGS 1
# define ERR_SOLITARY 2

# define T_SLOT 50000

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <philo.h>

typedef struct	s_data
{
	int				n_phi;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_slp;
	unsigned long	t_start;
	int				n_lun;
	int				stop;
	pthread_mutex_t	p_lock;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	pthread_t		*thread;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				lf;
	int				rf;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_slp;
	unsigned long	t_last;
	int				n_lun;
	int				alive;
	t_data			*data;
}					t_philo;

void	*function(void *arg);

/* === utils_generic === */
int				ft_atoi(const char *str);
unsigned long	ft_clock(unsigned long t_start);
void			ft_wait(int	t);
void			ft_print(t_philo *p, char *msg);

/* === utils_init === */
int		init(t_data *data, char **arr);
void	cleanup(t_data *data);
void	ft_create(t_data *data);

/* === utils_life === */
void	eat(t_philo	*p);
void	ft_sleep(t_philo *p);
void	think(t_philo *p);
#endif
