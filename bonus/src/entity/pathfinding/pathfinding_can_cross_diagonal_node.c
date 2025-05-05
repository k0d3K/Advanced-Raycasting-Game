/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_can_cross_diagonal_node.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:01:06 by dath              #+#    #+#             */
/*   Updated: 2025/04/14 18:01:21 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"

int	pf_can_cross_diagonal_node(t_pathfinding_vars *v, t_point p)
{
	t_tile	tile1;
	t_tile	tile2;
	int		diff1;
	int		diff2;

	if (!check_in_bounds(p.x, v->cur_node->p.y, v->map, NULL)
		|| !check_in_bounds(v->cur_node->p.x, p.y, v->map, NULL))
		return (0);
	tile1 = v->map->tile_data[v->cur_node->p.y][p.x];
	tile2 = v->map->tile_data[p.y][v->cur_node->p.x];
	diff1 = tile1.floor_height - v->cur_node->tile.floor_height;
	diff2 = tile2.floor_height - v->cur_node->tile.floor_height;
	return (diff1 == 0 && diff2 == 0);
}
