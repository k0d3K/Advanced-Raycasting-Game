/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:32:19 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/25 13:52:35 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_formats.h"

static void	print_hex_number(
	unsigned int n, int zero_pad, t_format_flags *flags, t_bool lowercase)
{
	if (flags->hashtag && n != 0)
	{
		if (lowercase)
			write(flags->fd, "0x", 2);
		else
			write(flags->fd, "0X", 2);
	}
	pad(flags->fd, zero_pad, '0');
	if (lowercase)
		print_decimal(flags->fd, n, 16, "0123456789abcdef");
	else
		print_decimal(flags->fd, n, 16, "0123456789ABCDEF");
}

int	print_hex(unsigned int n, t_format_flags *flags, t_bool lowercase)
{
	int		size;
	int		space_pad;
	int		zero_pad;
	t_bool	zero_dont_write;

	zero_dont_write = !n && flags->has_precision && flags->precision == 0;
	size = decimal_size(&n, FALSE, FALSE, 16);
	zero_pad = 0;
	if (flags->has_precision)
		zero_pad = max(flags->precision - size, 0);
	else if (flags->zero && !flags->minus)
		zero_pad = max(flags->minimum - size, 0);
	if (!zero_dont_write)
		size += 2 * flags->hashtag * (n != 0);
	space_pad = max(flags->minimum - size - zero_pad + zero_dont_write, 0);
	if (!flags->minus)
		pad(flags->fd, space_pad, ' ');
	if (!zero_dont_write)
		print_hex_number(n, zero_pad, flags, lowercase);
	if (flags->minus)
		pad(flags->fd, space_pad, ' ');
	return (size + zero_pad + space_pad - zero_dont_write);
}

int	print_ptr(void *n, t_format_flags *flags)
{
	int		size;
	int		space_pad;
	int		zero_pad;

	if (!n)
	{
		flags->precision = 6;
		return (print_string("(nil)", flags));
	}
	size = decimal_size(&n, FALSE, TRUE, 16);
	zero_pad = 0;
	if (flags->has_precision)
		zero_pad = max(flags->precision - size, 0);
	else if (flags->zero && !flags->minus)
		zero_pad = max(flags->minimum - size, 0);
	size += 2;
	space_pad = max(flags->minimum - size - zero_pad, 0);
	if (!flags->minus)
		pad(flags->fd, space_pad, ' ');
	write(flags->fd, "0x", 2);
	pad(flags->fd, zero_pad, '0');
	print_decimal(flags->fd, (unsigned long)n, 16, "0123456789abcdef");
	if (flags->minus)
		pad(flags->fd, space_pad, ' ');
	return (size + zero_pad + space_pad);
}
