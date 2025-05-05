/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:06:05 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/15 18:56:20 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_bool	add_string_slice(t_list **lst, t_string slice, int len)
{
	t_format_data	*data;
	t_list			*new;

	len = min(len, ft_strlen(slice.s));
	if (len <= 0)
		return (TRUE);
	data = ft_calloc(1, sizeof(t_format_data));
	if (!data)
		return (FALSE);
	slice.len = len;
	data->slice = slice;
	new = ft_lstnew(0);
	if (!new)
	{
		free(data);
		return (FALSE);
	}
	(*lst)->content = data;
	(*lst)->next = new;
	*lst = new;
	return (TRUE);
}

static t_bool	add_format_data(t_list **lst, t_format_data *fmt_data)
{
	t_list	*new;

	new = ft_lstnew(0);
	if (!new)
	{
		free(fmt_data);
		return (FALSE);
	}
	(*lst)->content = fmt_data;
	(*lst)->next = new;
	*lst = new;
	return (TRUE);
}

static t_bool	fill_list(char *format, t_list *lst)
{
	t_string		slice;
	t_format_data	*fmt_data;
	t_bool			valid_fmt;
	int				increment;

	slice.s = format;
	while (*format)
	{
		while (*format == '%')
		{
			fmt_data = parse_format_data(format, &valid_fmt, &increment);
			if (!fmt_data && increment == -1)
				return (FALSE);
			if (valid_fmt)
			{
				if (!add_string_slice(&lst, slice, format - slice.s)
					|| !add_format_data(&lst, fmt_data))
					return (FALSE);
				slice.s = format + increment;
			}
			format += increment;
		}
		format += !!*format;
	}
	return (add_string_slice(&lst, slice, format - slice.s));
}

t_list	*parse_format(const char *format)
{
	t_list	*res;
	t_list	*cur;

	res = ft_lstnew(0);
	if (!res)
		return (0);
	if (!fill_list((char *)format, res))
	{
		ft_lstclear(&res, free);
		return (0);
	}
	cur = res;
	if (cur->next)
	{
		while (cur->next->next)
			cur = cur->next;
		ft_lstdelone(cur->next, free);
		cur->next = NULL;
	}
	return (res);
}
