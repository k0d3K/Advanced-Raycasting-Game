/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_resources.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:50:37 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 16:37:52 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"
#include "utils.h"
#include <stdlib.h>

int	pathfinding_init_resources(t_pathfinding_resources *res, t_map *map)
{
	uint8_t			**traversed_nodes;
	int				i;
	const uint32_t	max_capacity = map->width * map->height;

	traversed_nodes = malloc((map->height + 1) * sizeof(char *));
	if (!traversed_nodes)
		return (0);
	i = -1;
	while (++i < map->height)
	{
		traversed_nodes[i] = malloc(map->width * sizeof(char));
		if (!traversed_nodes[i])
		{
			ft_free_matrix((void **)traversed_nodes, i);
			return (0);
		}
	}
	traversed_nodes[i] = NULL;
	if (!node_list_init(&res->node_list, max_capacity))
	{
		ft_free_matrix((void **)traversed_nodes, i);
		return (0);
	}
	res->traversed_nodes = traversed_nodes;
	return (1);
}

void	pathfinding_free_resources(t_pathfinding_resources *res)
{
	free(res->node_list.pool.arr);
	res->node_list.pool.arr = NULL;
	if (res->traversed_nodes)
		ft_clean_matrix((void **)res->traversed_nodes);
	res->traversed_nodes = NULL;
}
