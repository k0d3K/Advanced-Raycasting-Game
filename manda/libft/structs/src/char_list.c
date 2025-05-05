/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:37:07 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/04 00:23:49 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_list.h"
#include "libft.h"
#include <assert.h>

int	char_list_init(t_char_list *lst, size_t init_cap)
{
	lst->cap = init_cap;
	lst->len = 0;
	lst->arr = ft_calloc(lst->cap, sizeof(char));
	return (!!lst->arr);
}

int	char_list_add(t_char_list *lst, char tok)
{
	char	*new_list;

	if (!lst->arr)
		return (0);
	if (lst->len == lst->cap)
	{
		new_list = ft_realloc(lst->arr,
				lst->cap * sizeof(char),
				LIST_INCREMENT * sizeof(char));
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

void	char_list_remove(t_char_list *lst, size_t start, size_t n)
{
	if (!lst->arr || !n)
		return ;
	assert(start + n - 1 < lst->len);
	ft_memmove(&lst->arr[start],
		&lst->arr[start + n],
		(lst->len - n) * sizeof(char));
	ft_bzero(&lst->arr[lst->len - n], n * sizeof(char));
	lst->len -= n;
}

size_t	char_list_indexof(t_char_list *lst, char o)
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

int	char_list_contains(t_char_list *lst, char o)
{
	return (char_list_indexof(lst, o) != (size_t)-1);
}
