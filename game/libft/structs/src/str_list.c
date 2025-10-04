/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:37:07 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/04 00:20:30 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_list.h"
#include "libft.h"
#include <assert.h>

int	str_list_init(t_str_list *lst, size_t init_cap,	
		int components_are_allocated)
{
	lst->cap = init_cap;
	lst->len = 0;
	lst->components_are_allocated = components_are_allocated;
	lst->arr = ft_calloc(lst->cap, sizeof(char *));
	return (!!lst->arr);
}

int	str_list_add(t_str_list *lst, char *tok)
{
	char	**new_arr;

	if (!lst->arr)
		return (0);
	if (lst->len == lst->cap)
	{
		new_arr = ft_realloc(lst->arr,
				lst->cap * sizeof(char *),
				LIST_INCREMENT * sizeof(char *));
		if (!new_arr)
		{
			str_list_free(lst);
			return (0);
		}
		lst->arr = new_arr;
		lst->cap += LIST_INCREMENT;
	}
	lst->arr[lst->len++] = tok;
	return (1);
}

void	str_list_remove(t_str_list *lst, size_t start, size_t n)
{
	if (!lst->arr)
		return ;
	assert(start + n - 1 < lst->len);
	if (lst->components_are_allocated)
		free_list_range((t_generic_list *)lst, start, start + n);
	ft_memmove(&lst->arr[start],
		&lst->arr[start + n],
		(lst->len - n) * sizeof(char *));
	ft_bzero(&lst->arr[lst->len - n], n * sizeof(char *));
	lst->len -= n;
}

size_t	str_list_indexof(t_str_list *lst, char *o)
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

int	str_list_contains(t_str_list *lst, char *o)
{
	return (str_list_indexof(lst, o) != (size_t)-1);
}
