/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:19:01 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/12 20:24:48 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"
#include <stdlib.h>
#include <assert.h>

int	node_pool_init(t_node_pool *pool, uint32_t capacity)
{
	pool->capacity = capacity;
	pool->idx = 0;
	pool->arr = malloc(capacity * sizeof(t_node));
	if (!pool->arr)
		return (0);
	return (1);
}

t_node	*node_pool_fetch(t_node_pool *pool)
{
	void	*obj;

	assert(pool->arr);
	assert(pool->idx + 1 != pool->capacity);
	obj = &pool->arr[pool->idx++];
	return (obj);
}
