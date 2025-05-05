/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:42:38 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/20 16:45:54 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <assert.h>

void	*ft_realloc(void *ptr, ssize_t ptr_size, ssize_t add_size)
{
	void	*new;
	ssize_t	total;

	total = ptr_size + add_size;
	assert(ptr_size >= 0 && total >= 0);
	new = malloc(total);
	if (!new)
		return (0);
	if (ptr_size != 0)
	{
		if (add_size < 0)
			ft_memcpy(new, ptr, total);
		else
		{
			ft_memcpy(new, ptr, ptr_size);
			ft_bzero(new + ptr_size, add_size);
		}
	}
	else
		ft_bzero(new, ptr_size);
	free(ptr);
	return (new);
}
