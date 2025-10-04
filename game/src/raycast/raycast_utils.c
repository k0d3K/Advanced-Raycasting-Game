/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:27:38 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/29 19:27:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "utils.h"
#include "gfx.h"
#include <math.h>

#ifdef DEBUG

void	safe_put(t_gfx *gfx, t_vec2 pos)
{
	const t_point	p = {{TRUE_WIN_W + pos.x * UI_SCALE, pos.y * UI_SCALE}};

	if (p.x >= TRUE_WIN_W && p.x < WIN_W && p.y >= 0 && p.y < WIN_H)
	{
		gfx_put(gfx, p, WHITE);
	}
}

#else

void	safe_put(t_gfx *gfx, t_vec2 pos)
{
	(void)gfx;
	(void)pos;
}

#endif

int	raycast_init(
	t_raycast_vars *v, t_vec2 dir, t_gfx *gfx, float max_distance)
{
	v->ppos = gfx->player.plane_pos;
	v->res.dist_from_ground = 0;
	v->pos = v->ppos;
	v->first = ' ';
	v->gfx = gfx;
	if (v->pos.x > 0 && v->pos.y > 0
		&& check_in_bounds(v->pos.x, v->pos.y, &gfx->map, &v->first))
		max_distance = raycast_calc_max_dist(v->pos, dir, gfx, max_distance);
	v->c = v->first;
	v->res.distance = 0;
	v->max_distance = max_distance;
	v->need_to_add_back = 0;
	v->cur_max_len = -1;
	v->previous_wall_height = 0;
	return (1);
}

void	get_door_height(t_raycast_vars *v, t_vec2 dir)
{
	t_vec2	pos;
	t_door	door;
	t_point	p;
	float	side_dist;

	pos = v->pos;
	door = v->tile.door;
	p = get_position(pos, dir);
	if (!door.orientation)
		side_dist = pos.x - p.x - 1 + door.status;
	else
		side_dist = pos.y - p.y - 1 + door.status;
	if (!door.orientation && pos.y - (int)pos.y >= 0.5 - DOOR_THICKNESS / 2
		&& pos.y - (int)pos.y <= 0.5 + DOOR_THICKNESS / 2 && side_dist < 0)
		v->res.wall_height = door.height;
	else if (door.orientation && pos.x - (int)pos.x >= 0.5 - DOOR_THICKNESS / 2
		&& pos.x - (int)pos.x <= 0.5 + DOOR_THICKNESS / 2 && side_dist < 0)
		v->res.wall_height = door.height;
	else
		v->res.wall_height = v->tile.floor_height;
}

void	fisrt_tile(t_raycast_vars *v, t_vec2 dir)
{
	t_vec2	opposite_dir;
	t_point	p;
	t_vec2	ppos;

	ppos = v->pos;
	opposite_dir.v = -dir.v;
	v->res.dir = dir;
	if (!next_coord(v, opposite_dir))
		return ;
	v->res.distance = -vec2_length((t_vec2)(v->pos.v - ppos.v));
	v->c = get_value_here(ppos, dir, &v->gfx->map);
	p = get_position(ppos, dir);
	v->tile = v->gfx->map.tile_data[p.y][p.x];
	if (v->c == 'D')
		get_door_height(v, dir);
	else
		v->res.wall_height = v->tile.floor_height;
	v->front = raycast_get_pos_on_texture(*v, dir);
	v->need_to_add_back = 1;
}
