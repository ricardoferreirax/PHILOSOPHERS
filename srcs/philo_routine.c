/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:48:25 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/05 20:04:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	handle_eating(t_philo *philo)
{
	if (!print_status(philo, "is eating"))
		return (0);
	pthread_mutex_lock(&philo->last_meal);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->last_meal);
	ft_usleep(philo->tt_eat, philo);
	pthread_mutex_lock(&philo->meal_count);
	if (philo->table->eat_count != 0)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_count);
	return (1);
}

static int	even_id_philo(t_philo *philo) // vai pegar no right e depois no left
{
	pthread_mutex_lock(philo->r_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->r_fork), 0);
	pthread_mutex_lock(philo->l_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->r_fork),
		pthread_mutex_unlock(philo->l_fork), 0);
	if (!handle_eating(philo))
		return (pthread_mutex_unlock(philo->r_fork),
		pthread_mutex_unlock(philo->l_fork), 0);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (1);
}

static int	odd_id_philo(t_philo *philo) // vai pegar no left e depois no right
{
	pthread_mutex_lock(philo->l_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->l_fork), 0);
	if (philo->table->philo_count == 1)
		return (pthread_mutex_unlock(philo->l_fork), 0);
	pthread_mutex_lock(philo->r_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->l_fork),
		pthread_mutex_unlock(philo->r_fork), 0);
	if (!handle_eating(philo))
		return (pthread_mutex_unlock(philo->l_fork),
		pthread_mutex_unlock(philo->r_fork), 0);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

static void	*philo_loop(t_philo *philo)
{
	while (1)
	{
		if (!print_status(philo, "is thinking"))
			return (NULL);
		usleep(500);
		if (philo->philo_id % 2 == 1)
		{
			if (!odd_id_philo(philo))
				return (NULL);
		}
		else
		{
			if (!even_id_philo(philo))
				return (NULL);
		}
		if (!print_status(philo, "is sleeping"))
			return (NULL);
		ft_usleep(philo->tt_sleep, philo);
	}
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (current_time_ms() < philo->start_sim)
		usleep(100);
	if (philo->philo_id % 2)
		usleep(100);
	return (philo_loop(philo));
}
