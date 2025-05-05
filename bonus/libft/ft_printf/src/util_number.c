/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:48:38 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/14 17:47:59 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

unsigned long	get_repr(
	void *n, t_bool is_signed, t_bool is_long, t_bool *is_neg)
{
	unsigned long	repr;

	*is_neg = 0;
	if (is_signed)
	{
		if (is_long)
		{
			*is_neg = (*(long *)n < 0);
			repr = ft_abs(*(long *)n);
		}
		else
		{
			*is_neg = (*(int *)n < 0);
			repr = ft_abs(*(int *)n);
		}
	}
	else
	{
		if (is_long)
			repr = *(unsigned long *)n;
		else
			repr = *(unsigned int *)n;
	}
	return (repr);
}

int	decimal_size(void *n, t_bool is_signed, t_bool is_long, int base)
{
	int				cnt;
	unsigned long	repr;
	t_bool			is_neg;

	cnt = 0;
	repr = get_repr(n, is_signed, is_long, &is_neg);
	cnt += is_neg;
	cnt += repr == 0;
	while (repr)
	{
		repr /= base;
		cnt++;
	}
	return (cnt);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

unsigned long	ft_abs(long n)
{
	return (n * (n > 0) - n * (n < 0));
}
