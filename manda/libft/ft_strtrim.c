/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:09:04 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/07 14:29:39 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_bounds(
	const char *s1, const char *set, const char **start, const char **end)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	*start = s1;
	while (**start && ft_strchr(set, **start))
		(*start)++;
	*end = s1 + len - 1;
	i = 0;
	while (i < len && ft_strchr(set, **end))
	{
		(*end)--;
		i++;
	}
	if (*end < *start)
		return (0);
	return ((size_t)(*end) - (size_t)(*start) + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*str;
	size_t		size;

	size = find_bounds(s1, set, &start, &end);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	ft_memcpy(str, start, size);
	str[size] = '\0';
	return (str);
}
