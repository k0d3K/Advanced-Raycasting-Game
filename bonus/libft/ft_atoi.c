/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:32:06 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/26 14:36:15 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	sign = 1;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
	}
	return (res * sign);
}

int	ft_checked_atoi(const char *format, int *did_parse)
{
	int			sign;
	long int	res;

	while (*format && *format == ' ')
		format++;
	sign = 1 - (*format == '-') * 2;
	format += (*format == '-' || *format == '+');
	res = 0;
	*did_parse = 1;
	if (!*format)
	{
		*did_parse = 0;
		return (0);
	}
	while (*format && *format >= '0' && *format <= '9')
	{
		res = res * 10 + (*format++ - '0');
		if (res < 0 || (res * sign < INT_MIN) || (res * sign > INT_MAX))
			*did_parse = 0;
	}
	*did_parse = *did_parse && !*format;
	return (res * sign);
}
