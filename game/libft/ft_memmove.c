/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:37:55 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/07 16:59:27 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	char		*end;
	const char	*src_ptr;

	dest_ptr = dest;
	src_ptr = src;
	if (src == dest)
		return (dest);
	if (dest_ptr > src_ptr && dest_ptr < (src_ptr + n))
	{
		end = dest_ptr - 1;
		dest_ptr += n - 1;
		src_ptr += n - 1;
		while (dest_ptr != end)
			*dest_ptr-- = *src_ptr--;
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}
