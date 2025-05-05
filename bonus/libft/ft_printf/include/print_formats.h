/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formats.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:22:47 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/25 13:46:54 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_FORMATS_H
# define PRINT_FORMATS_H

# include "parse.h"

int		print_string(char *str, t_format_flags *flags);
int		print_char(char c, t_format_flags *flags);

void	print_decimal(int fd, unsigned long n, int base, char *alpha);
int		print_unsigned_integer(unsigned int n, t_format_flags *flags);
int		print_integer(int n, t_format_flags *flags);
int		print_hex(unsigned int n,
			t_format_flags *flags, t_bool lowercase);
int		print_ptr(void *n, t_format_flags *flags);

#endif