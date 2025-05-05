/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:21:05 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/08 16:35:55 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <assert.h>
#include <string.h>

static void	build_table(uint32_t *table)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	cur_idx;
	uint32_t	crc;
	uint32_t	bit_state;

	i = 0;
	while (i < 256)
	{
		cur_idx = i;
		crc = 0;
		j = 0;
		while (j < 8)
		{
			bit_state = (cur_idx ^ crc) & 1;
			crc >>= 1;
			if (bit_state)
				crc ^= 0xEDB88320;
			cur_idx >>= 1;
			j++;
		}
		table[i++] = crc;
	}
}

uint32_t	str_crc32(char *str)
{
	static int		init = 0;
	static uint32_t	table[256];
	uint32_t		crc;
	size_t			i;
	size_t			len;

	assert(str);
	if (!init)
	{
		build_table(table);
		init = 1;
	}
	crc = 0xFFFFFFFF;
	len = strlen(str);
	i = 0;
	while (i < len)
	{
		crc = (crc >> 8)
			^ table[(str[i] ^ crc) & 0xFF];
		i++;
	}
	return (~crc);
}
