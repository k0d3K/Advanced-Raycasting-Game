/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:37:07 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/08 11:50:00 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uint_list.h"
#include "libft.h"
#include <assert.h>

int	uint_list_init(t_uint_list *lst, size_t init_cap)
{
	lst->cap = init_cap;
	lst->len = 0;
	lst->arr = ft_calloc(lst->cap, sizeof(uint32_t));
	return (!!lst->arr);
}

int	uint_list_add(t_uint_list *lst, uint32_t tok)
{
	uint32_t	*new_list;

	if (!lst->arr)
		return (0);
	if (lst->len == lst->cap)
	{
		new_list = ft_realloc(lst->arr,
				lst->cap * sizeof(uint32_t),
				LIST_INCREMENT * sizeof(uint32_t));
		if (!new_list)
		{
			free(lst->arr);
			lst->arr = NULL;
			return (0);
		}
		lst->arr = new_list;
		lst->cap += LIST_INCREMENT;
	}
	lst->arr[lst->len++] = tok;
	return (1);
}

void	uint_list_remove(t_uint_list *lst, size_t start, size_t n)
{
	if (!lst->arr)
		return ;
	assert(start + n - 1 < lst->len);
	ft_memmove(&lst->arr[start],
		&lst->arr[start + n],
		(lst->len - n) * sizeof(uint32_t));
	ft_bzero(&lst->arr[lst->len - n], n * sizeof(uint32_t));
	lst->len -= n;
}

size_t	uint_list_indexof(t_uint_list *lst, uint32_t o)
{
	size_t	i;

	assert(!!lst->arr);
	i = 0;
	while (i < lst->len)
	{
		if (lst->arr[i] == o)
			return (i);
	}
	return ((size_t)-1);
}

int	uint_list_contains(t_uint_list *lst, uint32_t o)
{
	return (uint_list_indexof(lst, o) != (size_t)-1);
}
