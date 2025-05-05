/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_next_coord.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:30:51 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/05 15:30:23 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "map.h"
#include "gfx.h"

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
	t_point	p;

	p = get_position(pos, dir);
	border.x = p.x + (dir.x > 0);
	border.y = p.y + (dir.y > 0);
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
t_face	first_border_hit(t_vec2 pos, t_vec2 dir, t_vec2 border)
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
 * @brief Find the next position of the ray.
 * 
 * @param pos The current position of the ray.
 * @param dir The direction of the ray.
 * @param border The borders of the next tile hit by the ray.
 * @param border_t The type of the border hit.
 * 
 * @return The vector of the next position of the ray.
 */
static t_vec2	find_next_pos(
	t_vec2 pos, t_vec2 dir, t_vec2 border, t_face border_t)
{
	t_vec2	res;

	if (border_t == NORTH || border_t == SOUTH)
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

static void	door_border_type(t_raycast_vars *v, t_vec2 dir, t_vec2 border)
{
	t_point	p;

	p = get_position(v->pos, dir);
	v->tile = v->gfx->map.tile_data[p.y][p.x];
	if (v->tile.door.orientation)
	{
		if (v->pos.x == border.x
			&& (v->res.wall_face == WEST || (v->res.wall_face == EAST)))
			v->res.wall_face = DOOR;
	}
	else
	{
		if (v->pos.y == border.y
			&& (v->res.wall_face == NORTH || (v->res.wall_face == SOUTH)))
			v->res.wall_face = DOOR;
	}
	if (v->res.wall_face == DOOR
		&& p.x == v->gfx->map.end_pos.x && p.y == v->gfx->map.end_pos.y)
		v->res.wall_face = EXIT;
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
int	next_coord(t_raycast_vars *v, t_vec2 dir)
{
	t_vec2	border;
	char	cur;
	t_point	p;

	cur = get_value_here(v->pos, dir, &v->gfx->map);
	p = get_position(v->pos, dir);
	if (check_in_bounds(p.x, p.y, &v->gfx->map, NULL))
		v->tile = v->gfx->map.tile_data[p.y][p.x];
	else
		return (0);
	if (cur == 'D')
		border = door_find_borders(v->pos, dir, v->tile);
	else
		border = find_borders(v->pos, dir);
	v->res.wall_face = first_border_hit(v->pos, dir, border);
	v->pos = find_next_pos(v->pos, dir, border, v->res.wall_face);
	p = get_position(v->pos, dir);
	if (check_in_bounds(p.x, p.y, &v->gfx->map, NULL))
		v->tile = v->gfx->map.tile_data[p.y][p.x];
	cur = get_value_here(v->pos, dir, &v->gfx->map);
	if (cur == 'D')
		door_border_type(v, dir, border);
	v->c = cur;
	return (1);
}
