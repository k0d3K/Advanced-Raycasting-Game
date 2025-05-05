/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:28:10 by dath              #+#    #+#             */
/*   Updated: 2025/04/09 14:38:35 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "strings.h"
#include <stdio.h>

void	error(char *fmt, ...)
{
	va_list	va;

	va_start(va, fmt);
	ft_putstr_fd(ERROR_TEXT, 2);
	vfprintf(stderr, fmt, va);
	ft_putchar_fd('\n', 2);
	va_end(va);
}
