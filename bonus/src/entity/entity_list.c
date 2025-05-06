/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:36:40 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 16:11:00 by tjouvenc         ###   ########.fr       */
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
