/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_dist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:32:10 by dath              #+#    #+#             */
/*   Updated: 2025/04/15 19:50:16 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "gfx.h"

static __always_inline void	calc_line1(
	t_vec2_pair *line1, t_vec2 dir, t_map *map)
{
	if (dir.x > 0)
	{
		line1->a = (t_vec2){{map->width, 0}};
		line1->b = (t_vec2){{map->width, map->height}};
	}
	else
	{
		line1->a = (t_vec2){{0, 0}};
		line1->b = (t_vec2){{0, map->height}};
	}
}

static __always_inline void	calc_line2(
	t_vec2_pair *line2, t_vec2 dir, t_map *map)
{
	if (dir.y > 0)
	{
		line2->a = (t_vec2){{0, map->height}};
		line2->b = (t_vec2){{map->width, map->height}};
	}
	else
	{
		line2->a = (t_vec2){{0, 0}};
		line2->b = (t_vec2){{map->width, 0}};
	}
}

float	raycast_calc_max_dist(
	t_vec2 ppos, t_vec2 dir, t_gfx *gfx, float prev_max_dist)
{
	float		max_dist;
	t_vec2_pair	line1;
	t_vec2_pair	line2;
	t_vec2_pair	intersections;
	t_vec2		end_pos;

	calc_line1(&line1, dir, &gfx->map);
	calc_line2(&line2, dir, &gfx->map);
	end_pos.x = ppos.x + dir.x * prev_max_dist;
	end_pos.y = ppos.y + dir.y * prev_max_dist;
	intersections.a = geo_intersection(ppos, end_pos, line1.a, line1.b);
	intersections.b = geo_intersection(ppos, end_pos, line2.a, line2.b);
	if (!isnan(intersections.a.x) && !isnan(intersections.a.y))
		max_dist = vec2_length((t_vec2)(ppos.v - intersections.a.v));
	else if (!isnan(intersections.b.x) && !isnan(intersections.b.y))
		max_dist = vec2_length((t_vec2)(ppos.v - intersections.b.v));
	else
		max_dist = prev_max_dist;
	if (prev_max_dist < max_dist)
		return (prev_max_dist);
	return (max_dist);
}

t_raycast	raycast_get_pos_on_texture(t_raycast_vars v, t_vec2 dir)
{
	if (v.res.wall_face == NORTH || v.res.wall_face == SOUTH
		|| (v.res.wall_face >= DOOR && !v.tile.door.orientation))
	{
		if (dir.y > 0)
			v.res.x_ratio = ceilf(v.pos.x) - v.pos.x;
		else
			v.res.x_ratio = v.pos.x - floorf(v.pos.x);
		if (v.res.wall_face >= DOOR)
			v.res.x_ratio += v.tile.door.status * ((dir.y < 0) - (dir.y > 0));
	}
	else if (v.res.wall_face == EAST || v.res.wall_face == WEST
		|| (v.res.wall_face >= DOOR && v.tile.door.orientation))
	{
		if (dir.x < 0)
			v.res.x_ratio = ceilf(v.pos.y) - v.pos.y;
		else
			v.res.x_ratio = v.pos.y - floorf(v.pos.y);
		if (v.res.wall_face >= DOOR)
			v.res.x_ratio += v.tile.door.status * ((dir.x > 0) - (dir.x < 0));
	}
	v.res.dir = dir;
	v.res.pos = v.tile.pos;
	return (v.res);
}
