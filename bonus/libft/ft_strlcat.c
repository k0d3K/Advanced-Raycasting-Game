/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:35:17 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/12 15:48:24 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;

	dest_len = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (*dst)
	{
		dst++;
		dest_len++;
	}
	if (dest_len >= size)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - dest_len - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dest_len + ft_strlen(src));
}
