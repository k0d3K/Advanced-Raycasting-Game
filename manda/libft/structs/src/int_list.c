/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:37:07 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/04 00:23:36 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_list.h"
#include "libft.h"
#include <assert.h>

int	int_list_init(t_int_list *lst, size_t init_cap)
{
	lst->cap = init_cap;
	lst->len = 0;
	lst->arr = ft_calloc(lst->cap, sizeof(int));
	return (!!lst->arr);
}

int	int_list_add(t_int_list *lst, int tok)
{
	int	*new_list;

	if (!lst->arr)
		return (0);
	if (lst->len == lst->cap)
	{
		new_list = ft_realloc(lst->arr,
				lst->cap * sizeof(int),
				LIST_INCREMENT * sizeof(int));
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

void	int_list_remove(t_int_list *lst, size_t start, size_t n)
{
	if (!lst->arr)
		return ;
	assert(start + n - 1 < lst->len);
	ft_memmove(&lst->arr[start],
		&lst->arr[start + n],
		(lst->len - n) * sizeof(int));
	ft_bzero(&lst->arr[lst->len - n], n * sizeof(int));
	lst->len -= n;
}

size_t	int_list_indexof(t_int_list *lst, int o)
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

int	int_list_contains(t_int_list *lst, int o)
{
	return (int_list_indexof(lst, o) != (size_t)-1);
}
