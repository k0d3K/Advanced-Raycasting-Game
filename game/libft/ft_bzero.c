/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:28:36 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/07 13:45:54 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static inline __attribute__((always_inline))
	void	bpb_bzero(char *dest, size_t n)
{
	char	*stop;

	stop = dest + n;
	while (dest != stop)
		*dest++ = 0;
}

static inline __attribute__((always_inline))
	void	small_bzero(uint32_t *dest, size_t n)
{
	if (n < 4)
		bpb_bzero((char *)dest, n);
	else
	{
		*dest++ = 0;
		if (n == 8)
			*dest = 0;
		else
			bpb_bzero((char *)dest, n - 4);
	}
}

static inline __attribute__((always_inline))
	void	big_bzero(uint64_t *dest, size_t n)
{
	uint64_t	*stop;

	stop = dest + n;
	while (dest != stop)
		*dest++ = 0;
}

void	ft_bzero(void *dest, size_t n)
{
	size_t	iter;
	size_t	rem;

	if (!n)
		return ;
	if (n < 8)
		small_bzero(dest, n);
	else
	{
		iter = n / 8;
		rem = n % 8;
		big_bzero(dest, iter);
		if (rem)
			small_bzero((uint32_t *)((uint64_t *)dest + iter), rem);
	}
}
