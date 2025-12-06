/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:45:49 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/05 14:57:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isnegative(const char *arg)
{
	if (arg[0] == '-')
	{
		printf("Error: argument cannot be negative\n");
		return (0);
	}
	return (1);
}

static int	ft_iszero(const char *arg)
{
	int i;

	i = 0;
	if (arg[i] == '+')
		i++;
	while (arg[i] == '0')
		i++;
	if (arg[i] == '\0')
	{
		printf("Error: argument cannot be zero\n");
		return (0);
	}
	return (1);
}

static int	ft_alldigits(const char *arg)
{
	int i;

	i = 0;
	if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("Error: all arguments must be digits\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	validate_int_limit(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	if ((len == 10 && ft_strncmp(str, "2147483647", 10) > 0)
		|| len > 10)
	{
		printf("Error: argument exceeds integer limit\n");
		return (0);
	}
	return (1);
}

int	validate_numbers(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_isnegative(av[i]))
			return (0);
		if (!ft_iszero(av[i]))
			return (0);
		if (!ft_alldigits(av[i]))
			return (0);
		if (!validate_int_limit(av[i]))
			return (0);
		i++;
	}
	return (1);
}
