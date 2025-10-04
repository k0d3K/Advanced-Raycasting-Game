/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:52:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/07 17:38:41 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

#define HIMAGIC	0x8080808080808080UL
#define LOMAGIC	0x0101010101010101UL

static inline __attribute__((always_inline))
	size_t	big_strlen(const char *beg,
			const uint64_t *longword_ptr,
			uint64_t longword,
			const char *cur)
{
	while (1)
	{
		longword = *longword_ptr++;
		if (((longword - LOMAGIC) & ~longword & HIMAGIC))
		{
			cur = (const char *)(longword_ptr - 1);
			if (cur[0] == 0)
				return (cur - beg);
			if (cur[1] == 0)
				return (cur - beg + 1);
			if (cur[2] == 0)
				return (cur - beg + 2);
			if (cur[3] == 0)
				return (cur - beg + 3);
			if (cur[4] == 0)
				return (cur - beg + 4);
			if (cur[5] == 0)
				return (cur - beg + 5);
			if (cur[6] == 0)
				return (cur - beg + 6);
			if (cur[7] == 0)
				return (cur - beg + 7);
		}
	}
}

size_t	ft_strlen(const char *str)
{
	const char		*ptr;

	ptr = str;
	while ((uint64_t)ptr & 7)
	{
		if (*ptr == '\0')
			return (ptr - str);
		ptr++;
	}
	return (big_strlen(str, (const uint64_t *)ptr, 0, 0));
}
