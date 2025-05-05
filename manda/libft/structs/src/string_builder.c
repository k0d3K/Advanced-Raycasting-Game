/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:16:48 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/07 14:43:21 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_builder.h"
#include "libft.h"
#include <stdio.h>

int	sb_appendn(t_sb *sb, char *str, size_t len)
{
	size_t	new_cap;

	printf("%zu\n", len);
	if (!sb->str)
		return (0);
	new_cap = len + sb->pos;
	if (new_cap > sb->capacity)
	{
		sb->str = ft_realloc(sb->str, sb->capacity, new_cap + 1000);
		if (!sb->str)
			return (0);
		sb->capacity += new_cap + 1000;
	}
	ft_memcpy((sb->str + sb->pos), str, len);
	sb->pos += len;
	return (1);
}

int	sb_append(t_sb *sb, char *str)
{
	return (sb_appendn(sb, str, ft_strlen(str)));
}

int	sb_addchar(t_sb *sb, char c)
{
	return (sb_appendn(sb, &c, 1));
}

int	sb_addu64(t_sb *sb, unsigned long long n)
{
	char	buf[21];
	char	*ptr;
	int		res;

	if (!n)
	{
		res = sb_addchar(sb, '0');
		return (res);
	}
	buf[20] = '\0';
	ptr = buf + 19;
	while (n)
	{
		*ptr-- = '0' + (n % 10);
		n /= 10;
	}
	res = sb_appendn(sb, ptr + 1, 19 - (ptr - buf));
	return (res);
}

int	sb_addi64(t_sb *sb, long long n)
{
	char	buf[21];
	char	*ptr;
	int		res;
	int		neg;

	if (!n)
	{
		res = sb_addchar(sb, '0');
		return (res);
	}
	neg = n < 0;
	n = n * !neg - n * neg;
	buf[20] = '\0';
	ptr = buf + 19;
	while (n)
	{
		*ptr-- = '0' + (n % 10);
		n /= 10;
	}
	if (neg)
		*ptr-- = '-';
	res = sb_appendn(sb, ptr + 1, 19 - (ptr - buf));
	return (res);
}
