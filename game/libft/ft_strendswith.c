/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:19:57 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/15 15:35:04 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strends_with(const char *s, const char *end)
{
	const size_t	s_len = ft_strlen(s);
	const size_t	end_len = ft_strlen(end);
	const char		*end_start = end;

	if (end_len > s_len)
		return (0);
	s += s_len - 1;
	end += end_len - 1;
	while (end >= end_start)
	{
		if (*s-- != *end--)
			return (0);
	}
	return (1);
}
