/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:34:30 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/25 13:35:49 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	pad(int fd, int n, char c)
{
	while (n-- > 0)
		ft_putchar_fd(c, fd);
}

size_t	ft_strnlen(const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *str)
	{
		str++;
		i++;
	}
	return (i);
}
