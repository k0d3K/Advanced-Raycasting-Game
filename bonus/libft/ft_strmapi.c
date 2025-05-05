/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:20:06 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/09 14:44:28 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	n;
	unsigned int	i;
	char			*str;

	n = (unsigned int)ft_strlen(s);
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (0);
	str[n] = '\0';
	i = 0;
	while (i < n)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}
