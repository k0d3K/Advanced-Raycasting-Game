/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:27:38 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/18 19:57:40 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "utils.h"
#include "gfx.h"
#include <math.h>

/**
 * @brief Find the distance from the player position to the
 * 		border in the specified direction.
 * 
 * @param ppos The player position.
 * @param dir The direction of the ray.
 * @param gfx The graphics structure.
 * @param max_distance The maximum distance the ray will travel
 *
 * @return Distance from the given position to the border.
 * 		   If the ray doesn't hit any border, return NAN.
 */
void	continuous_raycast(t_render_thread *rd, t_vec2 dir)
{
	t_raycast_vars	v;

	if (!raycast_init(&v, dir, rd->gfx, rd->gfx->max_raycast_distance))
		return ;
	fisrt_tile(&v, dir);
	while (v.res.distance < v.max_distance
		&& v.cur_max_len != rd->gfx->map.highest_wall)
	{
		if (!next_coord(&v, dir))
			break ;
		v.res.distance = vec2_length((t_vec2)(v.pos.v - v.ppos.v));
		if (v.need_to_add_back)
			raycast_add_back(&v, dir, rd->rcs, &rd->rcs_len);
		if (v.c == 'D')
			get_door_height(&v, dir);
		else
			v.res.wall_height = get_wall_height(v.c);
		if (v.res.wall_height >= 0
			&& (v.res.wall_height < rd->gfx->player.pos.z
				|| v.res.wall_height > v.cur_max_len))
		{
			safe_put(rd->gfx, v.pos);
			raycast_add_front(&v, dir);
		}
	}
}

/**
 * @brief Find the distance from the player position to the
 * 		border in the specified direction.
 * 
 * @param ppos The player position.
 * @param dir The direction of the ray.
 * @param gfx The graphics structure.
 * @param max_distance The maximum distance the ray will travel
 *
 * @return Distance from the given position to the border.
 * 		   If the ray doesn't hit any border, return NAN.
 */
t_raycast	raycast(t_gfx *gfx, t_vec3 pos, t_vec2 dir, float max_distance)
{
	t_raycast_vars	v;

	v.ppos = (t_vec2){{pos.x, pos.y}};
	if (!raycast_init(&v, dir, gfx, max_distance))
		return (g_empty_raycast);
	while (v.res.distance < v.max_distance)
	{
		v.res.wall_height = get_wall_height(v.c);
		if (!next_coord(&v, dir))
			return (g_empty_raycast);
		v.res.distance = vec2_length((t_vec2)(v.pos.v - v.ppos.v));
		safe_put(gfx, v.pos);
		if (v.c == 'D')
			get_door_height(&v, dir);
		else
			v.res.wall_height = get_wall_height(v.c);
		if (v.res.wall_height > pos.z)
			break ;
	}
	return (raycast_get_pos_on_texture(v, dir));
}
