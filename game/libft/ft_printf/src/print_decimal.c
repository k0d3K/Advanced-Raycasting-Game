/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:56:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/25 14:17:51 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_formats.h"

static void	print_decimal_rec(int fd, unsigned long n, int base, char *alpha)
{
	if (n == 0)
		return ;
	print_decimal_rec(fd, n / base, base, alpha);
	ft_putchar_fd(alpha[n % base], fd);
}

void	print_decimal(int fd, unsigned long n, int base, char *alpha)
{
	if (n == 0)
		ft_putchar_fd(alpha[0], fd);
	else
		print_decimal_rec(fd, n, base, alpha);
}
