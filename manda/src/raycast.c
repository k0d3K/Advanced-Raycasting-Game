/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:40:17 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/10 19:41:52 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "gfx.h"
#include "map.h"
#include <math.h>

/**
 * @brief Find the borders of the next tile hit by the ray.
 * 
 * @param pos The current position of the ray.
 * @param dir The direction of the ray.
 * 
 * @return The vector of the borders of the next tile hit by the ray.
 */
static t_vec2	find_borders(t_vec2 pos, t_vec2 dir)
{
	t_vec2	border;

	if (dir.x < 0)
		border.x = ceilf(pos.x) - 1;
	else if (dir.x == 0)
		border.x = pos.x;
	else
		border.x = floorf(pos.x) + 1;
	if (dir.y < 0)
		border.y = ceilf(pos.y) - 1;
	else if (dir.y == 0)
		border.y = pos.y;
	else
		border.y = floorf(pos.y) + 1;
	return (border);
}

/**
 * @brief Find the first border hit by the ray.
 * 
 * @param pos The current position of the ray.
 * @param dir The direction of the ray.
 * @param border The borders of the next tile hit by the ray.
 * 
 * @return The type of the border hit.
 */
static t_cardinal	first_border_hit(t_vec2 pos, t_vec2 dir, t_vec2 border)
{
	t_vec2	t;

	if (dir.x == 0)
		t.x = 1;
	else
		t.x = (border.x - pos.x) / dir.x;
	if (dir.y == 0)
		t.y = 1;
	else
		t.y = (border.y - pos.y) / dir.y;
	if (t.x > t.y)
	{
		if (dir.y > 0)
			return (NORTH);
		return (SOUTH);
	}
	if (dir.x > 0)
		return (WEST);
	return (EAST);
}

/**
 * @brief Find the next coordinates of the ray.
 * 
 * @param pos The current position of the ray.
 * @param dir The direction of the ray.
 * @param border_type A pointer to the type of the border hit.
 * 
 * @return The vector of next coordinates of the ray.
 * 		   The type of the border hit is stored in border_type.
 */
static t_vec2	next_coord(t_vec2 pos, t_vec2 dir, t_cardinal *border_type)
{
	t_vec2	border;
	t_vec2	res;

	border = find_borders(pos, dir);
	*border_type = first_border_hit(pos, dir, border);
	if (*border_type == NORTH || *border_type == SOUTH)
	{
		res.y = border.y;
		if (dir.y == 0)
			res.x = pos.x + dir.x;
		else
			res.x = pos.x + (dir.x * (border.y - pos.y)) / dir.y;
	}
	else
	{
		res.x = border.x;
		if (dir.x == 0)
			res.y = pos.y + dir.y;
		else
			res.y = pos.y + (dir.y * (border.x - pos.x)) / dir.x;
	}
	return (res);
}

static t_raycast	get_pos_on_image(t_raycast res, t_cardinal border_type,
	t_vec2 pos, t_vec2 dir)
{
	if (border_type == NORTH || border_type == SOUTH)
	{
		if (dir.y > 0)
			res.x_ratio = ceilf(pos.x) - pos.x;
		else
			res.x_ratio = pos.x - floorf(pos.x);
	}
	else
	{
		if (dir.x < 0)
			res.x_ratio = ceilf(pos.y) - pos.y;
		else
			res.x_ratio = pos.y - floorf(pos.y);
	}
	return (res);
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
t_raycast	raycast(t_vec2 ppos, t_vec2 dir, t_gfx *gfx, float max_distance)
{
	char		first;
	char		c;
	t_vec2		pos;
	t_raycast	res;

	first = ' ';
	pos = ppos;
	if (ppos.x > 0 && ppos.y > 0 && check_in_bounds(pos.x, pos.y, &gfx->map))
		first = gfx->map.map[(int)pos.y][(int)pos.x];
	res.distance = 0;
	while (res.distance < max_distance)
	{
		pos = next_coord(pos, dir, &res.wall_face);
		c = get_value_here(pos, dir, res.wall_face, &gfx->map);
		res.distance = vec2_length((t_vec2)(pos.v - ppos.v));
		if ((c == '1' && first != '1') || (c != '1' && first == '1'))
			return (get_pos_on_image(res, res.wall_face, pos, dir));
	}
	res.distance = NAN;
	return (res);
}
