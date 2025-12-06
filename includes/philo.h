/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:51:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/05 19:46:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_sim t_sim;
typedef pthread_mutex_t t_mutex;

typedef struct s_philo
{
    int             philo_id;
    int             meals_eaten;
    long            tt_sleep;
    long            tt_die;
    long            tt_eat;
    long long       start_sim;
    long long       last_meal_time;
    t_mutex         *r_fork;
    t_mutex         *l_fork;
    t_mutex         last_meal;
    t_mutex         meal_count;
    pthread_t       thread_id;
    t_sim           *table; 
}   t_philo;

typedef struct s_sim
{
    int             philo_count;
    int             eat_count;
    int             someone_died;
    long            tt_sleep;
    long            tt_die;
    long            tt_eat;
    long long       start_sim;
    t_mutex         *forks;
    t_mutex         death_lock;
    t_mutex         print_lock;
    pthread_t       death_monitor;
    t_philo         *philos; 
}   t_sim;

int	print_status(t_philo *philo, const char *msg);
long long	current_time_ms(void);
void	ft_usleep(long long duration, t_philo *philo);
void	init_simulation(t_sim *sim);
void	*philo_routine(void *data);
void	*death_monitor(void *data);
int	validate_args(int ac, char **av, t_sim *sim);
int	validate_numbers(int ac, char **av);

int	ft_isdigit(int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

#endif