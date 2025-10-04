/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder_state.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:03:40 by theo              #+#    #+#             */
/*   Updated: 2025/02/07 14:33:47 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_builder.h"
#include "libft.h"

char	*sb_build(t_sb *sb)
{
	char	*res;

	if (!sb->str)
		return (0);
	res = malloc(sb->pos + 1);
	if (!res)
		return (0);
	ft_memcpy(res, sb->str, sb->pos);
	res[sb->pos] = '\0';
	sb->pos = 0;
	return (res);
}

int	sb_init(t_sb *sb, size_t init_cap)
{
	sb->capacity = init_cap;
	sb->pos = 0;
	sb->str = ft_calloc(sizeof(char), sb->capacity);
	return (!!sb->str);
}
