/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:48:25 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/04 16:33:27 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	even_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (!print_status(philo, "has taken a fork", philo->start_sim))
		return (pthread_mutex_unlock(philo->r_fork), 0);
	pthread_mutex_lock(philo->l_fork);
	if (!print_status(philo, "has taken a fork", philo->start_sim))
		return (pthread_mutex_unlock(philo->r_fork),
				pthread_mutex_unlock(philo->l_fork), 0);
	if (!print_status(philo, "is eating", philo->start_sim))
		return (pthread_mutex_unlock(philo->r_fork),
				pthread_mutex_unlock(philo->l_fork), 0);
	pthread_mutex_lock(&philo->last_meal);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->last_meal);
	ft_usleep(philo->tt_eat, philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&philo->meal_count);
	if (philo->table->eat_count != 0)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_count);
	return (1);
}

static int	odd_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (!print_status(philo, "has taken a fork", philo->start_sim))
		return (pthread_mutex_unlock(philo->l_fork), 0);
	if (philo->table->philo_count == 1)
		return (pthread_mutex_unlock(philo->l_fork), 0);
	pthread_mutex_lock(philo->r_fork);
	if (!print_status(philo, "has taken a fork", philo->start_sim))
		return (pthread_mutex_unlock(philo->l_fork),
				pthread_mutex_unlock(philo->r_fork), 0);
	if (!print_status(philo, "is eating", philo->start_sim))
		return (pthread_mutex_unlock(philo->l_fork),
				pthread_mutex_unlock(philo->r_fork), 0);
	pthread_mutex_lock(&philo->last_meal);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->last_meal);
	ft_usleep(philo->tt_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->meal_count);
	if (philo->table->eat_count != 0)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_count);
	return (1);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (current_time_ms() < philo->start_sim)
		usleep(100);
	if (philo->philo_id % 2)
		usleep(100);
	while (1)
	{
		if (!print_status(philo, "is thinking", philo->start_sim))
			return (NULL);
		if (philo->philo_id % 2 == 1)
		{
			if (!odd_philo(philo))
				return (NULL);
		}
		else
		{
			if (!even_philo(philo))
				return (NULL);
		}
		if (!print_status(philo, "is sleeping", philo->start_sim))
			return (NULL);
		ft_usleep(philo->tt_sleep, philo);
	}
	return (NULL);
}

