/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:19:22 by dath              #+#    #+#             */
/*   Updated: 2025/04/12 23:22:43 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"
#include <assert.h>

int	node_list_init(t_node_list *lst, uint32_t max_capacity)
{
	assert(lst);
	if (!node_pool_init(&lst->pool, max_capacity))
		return (0);
	lst->size = 0;
	lst->first = NULL;
	return (1);
}

void	node_list_clear(t_node_list *lst)
{
	lst->size = 0;
	lst->first = NULL;
	lst->pool.idx = 0;
}
