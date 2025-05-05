/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_adjacent_nodes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:44:44 by dath              #+#    #+#             */
/*   Updated: 2025/04/16 15:43:26 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"

static void	add_last_node(t_pathfinding_vars *v, t_point p, t_tile tile)
{
	t_node	node;

	node.p = p;
	node.tile = tile;
	node.parent_node = v->cur_node;
	node.h_cost = 0;
	node.g_cost = v->cur_node->g_cost;
	node.f_cost = v->cur_node->g_cost;
	node.tile = v->map->tile_data[p.y][p.x];
	v->end_node = node_pool_fetch(&v->open_list->pool);
	*v->end_node = node;
	return ;
}

static int	replace_node_at_same_pos(t_pathfinding_vars *v,
	t_point p, t_node node)
{
	t_node	*node_at_same_pos;

	node_at_same_pos = node_list_get_node_with_pos(v->open_list, p);
	if (node_at_same_pos)
	{
		if (node.g_cost < node_at_same_pos->g_cost)
		{
			node_at_same_pos->parent_node = v->cur_node;
			node_at_same_pos->g_cost = node.g_cost;
			node_at_same_pos->f_cost = node.g_cost + node_at_same_pos->h_cost;
		}
		return (1);
	}
	return (0);
}

static void	add_middle_node(t_pathfinding_vars *v,
	t_point p, int is_diagonal, t_tile tile)
{
	t_node	node;

	node.tile = tile;
	if (is_diagonal)
		node.g_cost = v->cur_node->g_cost + D_MOVEMENT_COST;
	else
		node.g_cost = v->cur_node->g_cost + H_V_MOVEMENT_COST;
	if (node.tile.floor_height >= v->map->highest_wall)
		return ;
	if (node.tile.floor_height - 1 == v->cur_node->tile.floor_height)
		node.g_cost += JUMP_COST;
	if (node.tile.type == T_DOOR && node.tile.door.state != OPENED)
		return ;
	if (replace_node_at_same_pos(v, p, node))
		return ;
	node.h_cost = pf_calculate_h_cost(v, p);
	node.f_cost = node.g_cost + node.h_cost;
	node.p = p;
	node.parent_node = v->cur_node;
	node_list_insert(v->open_list, node);
}

static void	add_node_if_unchecked(
	t_pathfinding_vars *v, t_point dir, int is_diagonal)
{
	t_tile			tile;
	t_point			p;
	char			c;

	p = (t_point)(v->cur_node->p.p + dir.p);
	if (v->end_node || !check_in_bounds(p.x, p.y, v->map, &c) || c == ' ')
		return ;
	if (is_diagonal && !pf_can_cross_diagonal_node(v, p))
		return ;
	tile = v->map->tile_data[p.y][p.x];
	if (tile.floor_height - 1 > v->cur_node->tile.floor_height)
		return ;
	if (p.x == v->end_pos.x && p.y == v->end_pos.y)
		add_last_node(v, p, tile);
	else if (!v->traversed_node_map[p.y][p.x])
		add_middle_node(v, p, is_diagonal, tile);
}

void	pf_add_all_adjacent_nodes(t_pathfinding_vars *v)
{
	add_node_if_unchecked(v, (t_point){{-1, -1}}, 1);
	add_node_if_unchecked(v, (t_point){{0, -1}}, 0);
	add_node_if_unchecked(v, (t_point){{1, -1}}, 1);
	add_node_if_unchecked(v, (t_point){{-1, 0}}, 0);
	add_node_if_unchecked(v, (t_point){{1, 0}}, 0);
	add_node_if_unchecked(v, (t_point){{-1, 1}}, 1);
	add_node_if_unchecked(v, (t_point){{0, 1}}, 0);
	add_node_if_unchecked(v, (t_point){{1, 1}}, 1);
}
