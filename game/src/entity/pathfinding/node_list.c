/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:20:21 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 16:34:03 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"
#include <stdlib.h>

t_node	*node_list_insert(t_node_list *lst, t_node node)
{
	t_node	*ptr;

	ptr = node_pool_fetch(&lst->pool);
	*ptr = node;
	ptr->next = lst->first;
	lst->first = ptr;
	lst->size++;
	return (ptr);
}

t_node	*node_list_get_node_with_pos(t_node_list *lst, t_point p)
{
	t_node	*cur;

	cur = lst->first;
	while (cur)
	{
		if (cur->p.x == p.x && cur->p.y == p.y)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

static void	remove_node_from_list(
		t_node_list *lst, t_node *smallest, t_node *node_before_smallest)
{
	if (!node_before_smallest)
		lst->first = lst->first->next;
	else
		node_before_smallest->next = smallest->next;
	lst->size--;
}

t_node	*node_list_fetch_least_costly_node(t_node_list *lst)
{
	t_node		*cur;
	t_node		*node_before_smallest;
	t_node		*smallest;
	uint32_t	smallest_cost;

	if (!lst->first)
		return (NULL);
	node_before_smallest = NULL;
	smallest = lst->first;
	smallest_cost = smallest->f_cost;
	cur = smallest;
	while (cur->next)
	{
		if (cur->next->f_cost < smallest_cost)
		{
			node_before_smallest = cur;
			smallest = node_before_smallest->next;
			smallest_cost = smallest->f_cost;
		}
		cur = cur->next;
	}
	remove_node_from_list(lst, smallest, node_before_smallest);
	return (smallest);
}
