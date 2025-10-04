/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:04:37 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/03 19:48:50 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "map.h"

#define STEP 0.0001f

t_vec2	door_borders(t_vec2 pos, t_point p, t_vec2 dir, float status)
{
	float	sign;
	t_vec2	border;

	sign = 1.0f * ((dir.y > 0) - (dir.y < 0));
	border.y = p.y + (dir.y > 0);
	border.x = p.x + (dir.x > 0);
	if (sign *(pos.y - p.y) < sign * 0.5f - DOOR_THICKNESS / 2)
		border.y += -sign * (0.5f + DOOR_THICKNESS / 2 - STEP);
	else if (sign *(pos.y - p.y) < sign * 0.5f + DOOR_THICKNESS / 2)
	{
		if (pos.x - p.x >= 1 - status && dir.x < 0)
			border.x += 1 - status - STEP;
		else if (pos.x - p.x <= 1 - status && dir.x > 0)
			border.x += -status + STEP;
		border.y += -sign * (0.5f - DOOR_THICKNESS / 2 - STEP);
	}
	return (border);
}

/**
 * @brief  Find the distance from the player position to the
 * 		door in the specified direction.
 * 		Also find the type of the border hit.
 * 
 * @param pos The position to check.
 * @param dir The direction of the ray.
 * @param wall_face The type of the border hit.
 * 
 * @return The value of the map at the given position.
 */
t_vec2	door_find_borders(t_vec2 pos, t_vec2 dir, t_tile tile)
{
	t_vec2	res;
	t_point	pos_int;

	pos_int = tile.pos;
	if (!tile.door.orientation)
		res = door_borders(pos, pos_int, dir, tile.door.status);
	else
	{
		pos = (t_vec2){{pos.y, pos.x}};
		dir = (t_vec2){{dir.y, dir.x}};
		pos_int = point(pos_int.y, pos_int.x);
		res = door_borders(pos, pos_int, dir, tile.door.status);
		res = (t_vec2){{res.y, res.x}};
	}
	return (res);
}
