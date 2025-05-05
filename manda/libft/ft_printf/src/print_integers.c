/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:55:21 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/25 13:53:38 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_formats.h"

int	print_unsigned_integer(unsigned int n, t_format_flags *flags)
{
	int		size;
	int		space_pad;
	int		zero_pad;
	t_bool	zero_dont_write;

	size = decimal_size(&n, FALSE, FALSE, 10);
	zero_dont_write = !n && flags->has_precision && flags->precision == 0;
	zero_pad = 0;
	if (flags->has_precision)
		zero_pad = max(flags->precision - size, 0);
	else if (flags->zero && !flags->minus)
		zero_pad = max(flags->minimum - size, 0);
	space_pad = max(flags->minimum - size - zero_pad + zero_dont_write, 0);
	if (!flags->minus)
		pad(flags->fd, space_pad, ' ');
	pad(flags->fd, zero_pad, '0');
	if (!zero_dont_write)
		print_decimal(flags->fd, n, 10, "0123456789");
	if (flags->minus)
		pad(flags->fd, space_pad, ' ');
	return (size + zero_pad + space_pad - zero_dont_write);
}

static int	calculate_zero_pad(
	int n, t_format_flags *flags, int *size, int one_before_number)
{
	int	zero_pad;

	zero_pad = 0;
	if (flags->has_precision)
	{
		zero_pad = max(flags->precision - *size + (n < 0), 0);
		*size += one_before_number;
	}
	else if (flags->zero && !flags->minus)
	{
		*size += one_before_number;
		zero_pad = max(flags->minimum - *size, 0);
	}
	else
		*size += one_before_number;
	return (zero_pad);
}

int	print_integer(int n, t_format_flags *flags)
{
	int		size;
	int		space_pad;
	int		zero_pad;
	t_bool	one_before_number;
	t_bool	zero_dont_write;

	size = decimal_size(&n, TRUE, FALSE, 10);
	one_before_number = (n >= 0) * (flags->plus + !flags->plus * flags->space);
	zero_dont_write = !n && flags->has_precision && flags->precision == 0;
	zero_pad = calculate_zero_pad(n, flags, &size, one_before_number);
	space_pad = max(flags->minimum - size - zero_pad + zero_dont_write, 0);
	if (!flags->minus)
		pad(flags->fd, space_pad, ' ');
	if (n < 0)
		ft_putchar_fd('-', flags->fd);
	else if (flags->plus && one_before_number)
		ft_putchar_fd('+', flags->fd);
	else if (flags->space && one_before_number)
		ft_putchar_fd(' ', flags->fd);
	pad(flags->fd, zero_pad, '0');
	if (!zero_dont_write)
		print_decimal(flags->fd, ft_abs(n), 10, "0123456789");
	if (flags->minus)
		pad(flags->fd, space_pad, ' ');
	return (size + zero_pad + space_pad - zero_dont_write);
}
