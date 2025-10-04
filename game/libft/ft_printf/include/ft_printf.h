/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:11:54 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 00:25:01 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_dprintf(int fd, const char *s, ...);
int	ft_vdprintf(int fd, const char *s, va_list va);

#endif
