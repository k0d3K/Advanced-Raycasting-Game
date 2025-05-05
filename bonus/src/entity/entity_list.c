/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:36:40 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/06 11:21:35 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"
#include "libft.h"
#include <assert.h>

int	entity_list_init(t_entity_list *lst, size_t init_cap)
{
	lst->cap = init_cap;
	lst->len = 0;
	lst->arr = ft_calloc(lst->cap, sizeof(t_entity));
	return (!!lst->arr);
}

int	entity_list_add(t_entity_list *lst, t_entity e)
{
	t_entity	*new_arr;

	if (!lst->arr)
		return (0);
	if (lst->len == lst->cap)
	{
		new_arr = ft_realloc(lst->arr,
				lst->cap * sizeof(t_entity),
				LIST_INCREMENT * sizeof(t_entity));
		if (!new_arr)
		{
			lst->arr = NULL;
			return (0);
		}
		lst->arr = new_arr;
		lst->cap += LIST_INCREMENT;
	}
	lst->arr[lst->len++] = e;
	return (1);
}

void	entity_list_remove(t_entity_list *lst, size_t start, size_t n)
{
	if (!lst->arr)
		return ;
	assert(start + n - 1 < lst->len);
	ft_memmove(&lst->arr[start],
		&lst->arr[start + n],
		(lst->len - n) * sizeof(t_entity));
	ft_bzero(&lst->arr[lst->len - n], n * sizeof(t_entity));
	lst->len -= n;
}
