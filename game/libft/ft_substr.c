/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:45:25 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/07 14:29:56 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*sub;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	i = 0;
	while ((start + i) < s_len && i < len)
		i++;
	sub = malloc(sizeof(char) * (i + 1));
	if (!sub)
		return (0);
	ft_memcpy(sub, &s[start], i);
	sub[i] = '\0';
	return (sub);
}
