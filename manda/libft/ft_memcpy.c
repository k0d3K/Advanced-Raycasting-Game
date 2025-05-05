/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:32:37 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/06 20:16:44 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static inline __attribute__((always_inline))
	void	bpb_copy(char *dest, const char *src, size_t n)
{
	char	*stop;

	stop = dest + n;
	while (dest != stop)
		*dest++ = *src++;
}

static inline __attribute__((always_inline))
	void	small_copy(uint32_t *dest, const uint32_t *src, size_t n)
{
	if (n < 4)
		bpb_copy((char *)dest, (const char *)src, n);
	else
	{
		*dest++ = *src++;
		if (n == 8)
			*dest = *src;
		else
			bpb_copy((char *)dest, (const char *)src, n - 4);
	}
}

static inline __attribute__((always_inline))
	void	big_copy(uint64_t *dest, const uint64_t *src, size_t n)
{
	uint64_t	*stop;

	stop = dest + n;
	while (dest != stop)
		*dest++ = *src++;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	iter;
	size_t	rem;

	if (dest == src || !n)
		return (dest);
	if (n < 8)
		small_copy(dest, src, n);
	else
	{
		iter = n / 8;
		rem = n % 8;
		big_copy(dest, src, iter);
		if (rem)
			small_copy((uint32_t *)((uint64_t *)dest + iter),
				(uint32_t *)((uint64_t *)src + iter),
				rem);
	}
	return (dest);
}
