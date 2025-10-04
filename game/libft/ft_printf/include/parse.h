/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:24:15 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/25 13:45:07 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include "util.h"

typedef struct s_format_flags
{
	int		fd;
	t_bool	minus;
	t_bool	zero;
	t_bool	space;
	t_bool	plus;
	t_bool	hashtag;
	t_bool	has_precision;
	int		precision;
	t_bool	has_minimum;
	int		minimum;
}	t_format_flags;

typedef struct s_string
{
	char	*s;
	int		len;
}	t_string;

typedef struct s_format_data
{
	t_string		slice;
	t_bool			valid_fmt;
	t_format_flags	format_flags;
	char			format_specifier;
}	t_format_data;

t_list			*parse_format(const char *format);
t_format_data	*parse_format_data(
					char *format, t_bool *valid_fmt, int *increment);

#endif