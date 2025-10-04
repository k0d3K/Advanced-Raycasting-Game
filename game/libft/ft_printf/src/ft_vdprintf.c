/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:11:18 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 00:25:25 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "parse.h"
#include "print_formats.h"
#include "util.h"
#include <stdio.h>

int	print_string(char *str, t_format_flags *flags)
{
	unsigned int	n;
	int				n_pad;

	if (!str)
	{
		if (flags->has_precision && flags->precision < 6)
			str = "";
		else
			str = "(null)";
	}
	if (flags->has_precision)
		n = ft_strnlen(str, (size_t)flags->precision);
	else
		n = ft_strlen(str);
	n_pad = 0;
	if (flags->has_minimum)
		n_pad = max(flags->minimum - n, 0);
	if (!flags->minus)
		pad(flags->fd, n_pad, ' ');
	write(flags->fd, str, n);
	if (flags->minus)
		pad(flags->fd, n_pad, ' ');
	return (n_pad + n);
}

int	print_char(char c, t_format_flags *flags)
{
	int	space_pad;

	space_pad = max(flags->minimum - 1, 0);
	if (!flags->minus)
		pad(flags->fd, space_pad, ' ');
	ft_putchar_fd(c, flags->fd);
	if (flags->minus)
		pad(flags->fd, space_pad, ' ');
	return (1 + space_pad);
}

static int	print_slice(int fd, t_string slice)
{
	if (!slice.len)
		return (0);
	write(fd, slice.s, slice.len - 1);
	if (slice.s[slice.len - 1] != '%' || slice.s[slice.len])
	{
		write(fd, &slice.s[slice.len - 1], 1);
		return (slice.len);
	}
	return (-1);
}

static int	print_data(t_format_data *fmt_data, va_list va, int total)
{
	char			spec;
	t_format_flags	*flags_ptr;
	int				count;

	spec = fmt_data->format_specifier;
	flags_ptr = &fmt_data->format_flags;
	count = 0;
	if (!fmt_data->valid_fmt || fmt_data->format_specifier == '%')
		count = print_slice(fmt_data->format_flags.fd, fmt_data->slice);
	else
	{
		if (spec == 's')
			count = print_string(va_arg(va, char *), flags_ptr);
		if (spec == 'd' || spec == 'i')
			count = print_integer(va_arg(va, int), flags_ptr);
		if (spec == 'u')
			count = print_unsigned_integer(va_arg(va, unsigned int), flags_ptr);
		if (spec == 'c')
			count = print_char((char)va_arg(va, int), flags_ptr);
		if (spec == 'x' || spec == 'X')
			count = print_hex(va_arg(va, unsigned int), flags_ptr, spec == 'x');
		if (spec == 'p')
			count = print_ptr(va_arg(va, void *), flags_ptr);
	}
	return ((total + count) * (count != -1) + -1 * (count == -1));
}

int	ft_vdprintf(int fd, const char *s, va_list va)
{
	t_list	*format;
	t_list	*cur;
	int		total;

	if (write(fd, 0, 0) == -1)
		return (-1);
	if (!s || !*s)
		return (-1 * (!s));
	format = parse_format(s);
	if (!format)
		return (-1);
	cur = format;
	total = 0;
	while (cur)
	{
		((t_format_data *)cur->content)->format_flags.fd = fd;
		total = print_data((t_format_data *)cur->content, va, total);
		cur = cur->next;
	}
	ft_lstclear(&format, free);
	return (total);
}
