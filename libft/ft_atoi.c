/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:30:45 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/05 16:02:11 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*checker(const char *str)
{
	while (*str == '\r' || *str == '\n' || *str == '\f'
		|| *str == '\v' || *str == '\t' || *str == ' ')
		str++;
	return ((char *)str);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	value;
	int	test;

	sign = 1;
	value = 0;
	str = checker(str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		test = value;
		value = value * 10 + sign * (*str - '0');
		if (sign == -1 && test < value)
			return (0);
		else if (sign == 1 && test > value)
			return (-1);
		str++;
	}
	return (value);
}
