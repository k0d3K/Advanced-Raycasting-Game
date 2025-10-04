/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:40:28 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/11/25 13:35:41 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "libft.h"
# include <unistd.h>

typedef unsigned char	t_bool;
# define TRUE 1
# define FALSE 0

int				min(int a, int b);
int				max(int a, int b);
void			pad(int fd, int n, char c);
unsigned long	ft_abs(long n);
size_t			ft_strnlen(const char *str, size_t n);
int				decimal_size(
					void *n, t_bool is_signed, t_bool is_long, int base);

#endif