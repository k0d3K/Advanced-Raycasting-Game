/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:38:08 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/15 18:28:23 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	parse_integer(char *format, int *i)
{
	int	power;
	int	res;
	int	old_res;
	int	orig_j;
	int	j;

	j = *i;
	orig_j = j;
	while (format[j] && ft_isdigit(format[j]))
		j++;
	j--;
	*i = j;
	power = 1;
	res = 0;
	old_res = -1;
	while (j >= orig_j)
	{
		res += (format[j] - '0') * power;
		if (res < old_res)
			return (-1);
		old_res = res;
		power *= 10;
		j--;
	}
	return (res);
}

static t_bool	is_valid_format_specifier(char c)
{
	return (
		c == 'x'
		|| c == 'X'
		|| c == 'd'
		|| c == 'c'
		|| c == 's'
		|| c == 'p'
		|| c == 'i'
		|| c == 'u'
		|| c == '%'
	);
}

static t_bool	assign_flags(char *format, int *i, t_format_flags *flags)
{
	if (format[*i] == '0')
		flags->zero = TRUE;
	else if (format[*i] == '-')
		flags->minus = TRUE;
	else if (format[*i] == '+')
		flags->plus = TRUE;
	else if (format[*i] == '#')
		flags->hashtag = TRUE;
	else if (format[*i] == ' ')
		flags->space = TRUE;
	else if (ft_isdigit(format[*i]))
	{
		flags->minimum = parse_integer(format, i);
		flags->has_minimum = flags->minimum >= 0;
		return (flags->has_minimum);
	}
	else if (format[*i] == '.')
	{
		(*i)++;
		flags->precision = parse_integer(format, i);
		flags->has_precision = flags->precision >= 0;
		return (flags->has_precision);
	}
	return (TRUE);
}

static t_bool	do_parse(char *format, int *i, t_format_data *fmt_data)
{
	t_format_flags	*flags;

	flags = &fmt_data->format_flags;
	while (format[*i] && !ft_isalpha(format[*i]) && format[*i] != '%'
		&& !flags->has_minimum && !flags->has_precision)
	{
		if (!assign_flags(format, i, &fmt_data->format_flags))
			return (FALSE);
		(*i)++;
	}
	if (!flags->has_precision && format[*i] && format[*i] == '.')
	{
		(*i)++;
		flags->precision = parse_integer(format, i);
		flags->has_precision = flags->precision >= 0;
		if (!flags->has_precision)
			return (FALSE);
		(*i)++;
	}
	if (!is_valid_format_specifier(format[*i]))
		return (FALSE);
	fmt_data->format_specifier = format[*i];
	(*i)++;
	return (TRUE);
}

t_format_data	*parse_format_data(
					char *format, t_bool *valid_fmt, int *increment)
{
	t_format_data	*fmt_data;

	fmt_data = ft_calloc(1, sizeof(t_format_data));
	if (!fmt_data)
	{
		*increment = -1;
		return (0);
	}
	*increment = 1;
	*valid_fmt = do_parse(format, increment, fmt_data);
	if (!*valid_fmt)
	{
		free(fmt_data);
		return (0);
	}
	fmt_data->slice.s = format;
	fmt_data->slice.len = *increment;
	if (fmt_data->format_specifier == '%')
		fmt_data->slice.len = 1;
	fmt_data->valid_fmt = TRUE;
	return (fmt_data);
}
