/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:45:49 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/04 16:33:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_valid_int(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	if ((len == 10 && ft_strncmp(str, "2147483647", 10) > 0) || len > 10)
		return (0);
	return (1);
}

static int	validate_numbers(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '-' || av[i][j] == '0')
			return (printf("Error: arguments cannot be negative or zero\n"), 0);
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (printf("Error: all arguments must be digitsc\n"), 0);
			j++;
		}
		if (!is_valid_int(av[i]))
			return (printf("Error: argument exceeds integer limits\n"), 0);
		i++;
	}
	return (1);
}

int	validate_args(int ac, char **av, t_sim *sim)
{
	if (!validate_numbers(ac, av))
		return (0);
	sim->philo_count = ft_atoi(av[1]);
	sim->tt_die = ft_atoi(av[2]);
	sim->tt_eat = ft_atoi(av[3]);
	sim->tt_sleep = ft_atoi(av[4]);
	sim->eat_count = 0;
	if (ac == 6)
		sim->eat_count = ft_atoi(av[5]);
	sim->someone_died = 0;
	return (1);
}
