/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:28:10 by dath              #+#    #+#             */
/*   Updated: 2025/03/08 00:31:11 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "strings.h"

void	error(char *fmt, ...)
{
	va_list	va;

	va_start(va, fmt);
	ft_putstr_fd(ERROR_TEXT, 2);
	ft_vdprintf(2, fmt, va);
	ft_putchar_fd('\n', 2);
	va_end(va);
}
