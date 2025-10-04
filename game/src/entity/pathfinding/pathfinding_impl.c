/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_impl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:02:27 by dath              #+#    #+#             */
/*   Updated: 2025/04/14 17:45:33 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"
#include "gfx.h"

static void	insert_first_node(
	t_pathfinding_vars *v, t_point start_pos, t_map *map)
{
	t_node	node;

	node.next = NULL;
	node.parent_node = NULL;
	node.p = start_pos;
	node.g_cost = 0;
	node.h_cost = pf_calculate_h_cost(v, start_pos);
	node.f_cost = node.h_cost;
	node.tile = map->tile_data[start_pos.y][start_pos.x];
	node_list_insert(v->open_list, node);
}

t_node	*pf_impl(t_point start_pos, t_point end_pos, t_gfx *gfx)
{
	t_pathfinding_vars	v;
	char				c;

	v.map = &gfx->map;
	if (!check_in_bounds(start_pos.x, start_pos.y, v.map, &c) || c == ' ')
		return (NULL);
	v.open_list = &gfx->pf_res.node_list;
	v.traversed_node_map = gfx->pf_res.traversed_nodes;
	v.end_pos = end_pos;
	v.end_node = NULL;
	insert_first_node(&v, start_pos, v.map);
	while (v.open_list->size && !v.end_node)
	{
		v.cur_node = node_list_fetch_least_costly_node(v.open_list);
		pf_add_all_adjacent_nodes(&v);
		v.traversed_node_map[v.cur_node->p.y][v.cur_node->p.x] = 1;
	}
	return (v.end_node);
}
