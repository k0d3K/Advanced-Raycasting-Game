/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:48:18 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/11 12:02:52 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_ptr;
	const unsigned char	*s2_ptr;
	size_t				i;

	s1_ptr = s1;
	s2_ptr = s2;
	i = 0;
	while (i < n)
	{
		if (s1_ptr[i] < s2_ptr[i])
			return (-1);
		else if (s1_ptr[i] > s2_ptr[i])
			return (1);
		i++;
	}
	return (0);
}
