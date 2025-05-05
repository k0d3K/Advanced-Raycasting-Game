/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:00:23 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/11 12:02:20 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static char	*alloc_str_from_integer_size(int n, int *len)
{
	*len = 0;
	if (n == INT_MIN)
		*len = 11;
	else
	{
		if (n < 0)
		{
			n = -n;
			(*len)++;
		}
		if (n <= 9)
			(*len)++;
		else
		{
			while (n != 0)
			{
				(*len)++;
				n /= 10;
			}
		}
	}
	return (malloc(sizeof(char) * (*len + 1)));
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;
	int		i;
	int		last_index;

	res = alloc_str_from_integer_size(n, &len);
	if (!res)
		return (0);
	res[len] = '\0';
	if (n == INT_MIN)
		return (ft_memcpy(res, "-2147483648", 11));
	last_index = 0;
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
		last_index = 1;
	}
	i = len - 1;
	while (i >= last_index)
	{
		res[i--] = '0' + (n % 10);
		n /= 10;
	}
	return (res);
}
