/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:46:36 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/09 14:42:11 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <limits.h>

static void	ft_putnbr_fd_rec(int n, int fd)
{
	if (n == 0)
		return ;
	ft_putnbr_fd_rec(n / 10, fd);
	ft_putchar_fd('0' + (n % 10), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		if (n <= 9)
			ft_putchar_fd('0' + n, fd);
		else
			ft_putnbr_fd_rec(n, fd);
	}
}
