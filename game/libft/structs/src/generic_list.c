/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:37:07 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/04 00:19:44 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_list.h"
#include "libft.h"
#include <assert.h>

int	generic_list_init(t_generic_list *lst, size_t init_cap,
		int components_are_allocated)
{
	lst->cap = init_cap;
	lst->len = 0;
	lst->components_are_allocated = components_are_allocated;
	lst->arr = ft_calloc(lst->cap, sizeof(void *));
	return (!!lst->arr);
}

int	generic_list_add(t_generic_list *lst, void *tok)
{
	void	**new_arr;

	if (!lst->arr)
		return (0);
	if (lst->len == lst->cap)
	{
		new_arr = ft_realloc(lst->arr,
				lst->cap * sizeof(void *),
				LIST_INCREMENT * sizeof(void *));
		if (!new_arr)
		{
			generic_list_free(lst);
			return (0);
		}
		lst->arr = new_arr;
		lst->cap += LIST_INCREMENT;
	}
	lst->arr[lst->len++] = tok;
	return (1);
}

void	generic_list_remove(t_generic_list *lst, size_t start, size_t n)
{
	if (!lst->arr)
		return ;
	assert(start + n - 1 < lst->len);
	if (lst->components_are_allocated)
		free_list_range(lst, start, start + n);
	ft_memmove(&lst->arr[start],
		&lst->arr[start + n],
		(lst->len - n) * sizeof(void *));
	ft_bzero(&lst->arr[lst->len - n], n * sizeof(void *));
	lst->len -= n;
}

size_t	generic_list_indexof(t_generic_list *lst, void *o)
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

int	generic_list_contains(t_generic_list *lst, void *o)
{
	return (generic_list_indexof(lst, o) != (size_t)-1);
}
