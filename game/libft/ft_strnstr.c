/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:00:08 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/11 12:09:51 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;

	len_little = 0;
	while (little[len_little])
		len_little++;
	if (len_little == 0 && (*big == '\0' || len == 0))
		return ((char *)big);
	i = 0;
	while (i != len && *big)
	{
		j = 0;
		while (i + j != len
			&& big[i + j] && little[j] && big[i + j] == little[j])
			j++;
		if (j == len_little)
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
