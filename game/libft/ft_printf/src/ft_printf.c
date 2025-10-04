/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:11:18 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 00:25:28 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	va;
	int		res;

	va_start(va, s);
	res = ft_vdprintf(1, s, va);
	va_end(va);
	return (res);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	va;
	int		res;

	va_start(va, s);
	res = ft_vdprintf(fd, s, va);
	va_end(va);
	return (res);
}
