/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:20:06 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/09 14:44:19 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	n;
	unsigned int	i;

	n = (unsigned int)ft_strlen(s);
	i = 0;
	while (i < n)
	{
		f(i, &s[i]);
		i++;
	}
}
