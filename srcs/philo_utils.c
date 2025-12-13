/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:44:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/13 16:24:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long long duration, t_philo *philo)
{
	long long	start;

	start = current_time_ms();
	while (current_time_ms() < start + duration)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->someone_died == 1)
		{
			pthread_mutex_unlock(&philo->table->death_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		usleep(100);
	}
}

void    cleanup_simulation(t_sim *sim, int created_threads)
{
    int i;

    i = 0;
    while (i < created_threads)
    {
        pthread_join(sim->philos[i].thread_id, NULL);
        i++;
    }
    if (created_threads == sim->philo_count)
        pthread_join(sim->death_monitor, NULL);
    i = 0;
    while (i < sim->philo_count)
    {
        pthread_mutex_destroy(&sim->forks[i]);
        pthread_mutex_destroy(&sim->philos[i].last_meal);
        pthread_mutex_destroy(&sim->philos[i].meal_count);
        i++;
    }
    pthread_mutex_destroy(&sim->print_lock);
    pthread_mutex_destroy(&sim->death_lock);
    free(sim->philos);
    free(sim->forks);
}
	
int	print_status(t_philo *philo, const char *msg)
{
	long long	now;

	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	now = current_time_ms();
	if (!philo->table->someone_died)
		printf("%lld %d %s\n", now - philo->start_sim, philo->philo_id, msg);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (1);
}
