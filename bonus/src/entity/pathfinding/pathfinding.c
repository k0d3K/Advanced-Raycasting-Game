/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:23:43 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:42:27 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"
#include "map.h"
#include "pathfinding.h"
#include "gfx.h"
#include <stdlib.h>
#include <math.h>
#include <sys/param.h>
#include <string.h>

static void	pf_post_fetch_target_position(
		t_gfx *gfx, t_entity *e, t_node *end_node, t_point end_point)
{
	t_node			*cur;
	t_node			*prev;
	t_point			prev_point;

	cur = end_node;
	prev = NULL;
	while (cur)
	{
		prev_point = end_point;
		if (prev)
			prev_point = prev->p;
		pf_debug_show_line(gfx, prev_point, cur->p);
		if (!cur->parent_node)
		{
			e->target_position = (t_vec2){{
				prev->p.x + 0.5f, prev->p.y + 0.5f}};
			e->dir = vec2_normalize((t_vec2)(
						e->target_position.v - e->plane_pos.v));
		}
		prev = cur;
		cur = cur->parent_node;
	}
}

static void	pf_calc_node_path(t_gfx *gfx, t_entity *e)
{
	int				i;
	t_point			start_point;
	t_point			end_point;
	t_node			*end_node;

	i = 0;
	while (i < gfx->map.height)
		memset(gfx->pf_res.traversed_nodes[i++], 0, gfx->map.width);
	node_list_clear(&gfx->pf_res.node_list);
	start_point.x = e->pos.x;
	start_point.y = e->pos.y;
	end_point.x = gfx->player.pos.x;
	end_point.y = gfx->player.pos.y;
	end_node = pf_impl(start_point, end_point, gfx);
	e->can_reach_player = !!end_node;
	if (end_node)
		pf_post_fetch_target_position(gfx, e, end_node, end_point);
}

#ifdef DEBUG

void	pathfinding_calc_path(t_gfx *gfx, t_entity *e)
{
	t_raycast	rc;
	t_vec2		dir;

	if (!e->player_dist.x && !e->player_dist.y)
		return ;
	dir = vec2_normalize(e->player_dist);
	rc = raycast(gfx, e->pos, dir, e->dist_to_player);
	if (isnan(rc.distance) || rc.distance > e->dist_to_player)
	{
		e->dir = dir;
		e->target_position = gfx->player.plane_pos;
		e->can_reach_player = 1;
	}
	else
		pf_calc_node_path(gfx, e);
	e->need_to_refresh_pathfinding = 0;
}

#else

void	pathfinding_calc_path(t_gfx *gfx, t_entity *e)
{
	t_raycast	rc;
	t_vec2		dir;

	if (!e->need_to_refresh_pathfinding)
		return ;
	if (!e->player_dist.x && !e->player_dist.y)
		return ;
	dir = vec2_normalize(e->player_dist);
	rc = raycast(gfx, e->pos, dir, e->dist_to_player);
	if (isnan(rc.distance) || rc.distance > e->dist_to_player)
	{
		e->dir = dir;
		e->target_position = gfx->player.plane_pos;
		e->can_reach_player = 1;
	}
	else
		pf_calc_node_path(gfx, e);
	e->need_to_refresh_pathfinding = 0;
}

#endif
