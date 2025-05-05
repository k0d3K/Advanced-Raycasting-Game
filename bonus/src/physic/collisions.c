/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:53:56 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/05 15:30:47 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "raycast.h"
#include "collision.h"
#include <sys/param.h>

static int	check_block_collisions(t_caps *sphere, t_tile tile, t_point check)
{
	t_aabb	box;

	box.pos.x = check.x;
	box.pos.y = check.y;
	box.pos.z = 0;
	box.size.x = 1;
	box.size.y = 1;
	box.size.z = tile.floor_height;
	if (aabb_capsule_collision(box, sphere))
		return (1);
	return (0);
}

static int	check_door_collisions(t_caps *sphere, t_tile tile, t_point check)
{
	t_aabb	box;

	if (tile.door.orientation)
	{
		box.pos.x = check.x + 0.5 - DOOR_THICKNESS / 2;
		box.pos.y = check.y;
		box.size.x = DOOR_THICKNESS;
		box.size.y = 1 - tile.door.status;
	}
	else
	{
		box.pos.x = check.x;
		box.pos.y = check.y + 0.5 - DOOR_THICKNESS / 2;
		box.size.x = 1 - tile.door.status;
		box.size.y = DOOR_THICKNESS;
	}
	box.pos.z = 0;
	box.size.z = tile.door.height;
	if (aabb_capsule_collision(box, sphere))
		return (1);
	return (0);
}

int	check_tile_collision(t_map *map, t_caps *capsule, t_point check, int *hit)
{
	t_tile	tile;

	if (!check_in_bounds(check.x, check.y, map, NULL))
		return (0);
	tile = map->tile_data[check.y][check.x];
	*hit = check_block_collisions(capsule, tile, check) || *hit;
	if (tile.type == T_DOOR)
		*hit = check_door_collisions(capsule, tile, check) || *hit;
	return (1);
}

void	collision_effect(t_gfx *gfx, t_entity *e, int *hit)
{
	t_vec2		dir;

	if (e->type == T_COIN)
		e->is_dead = 1;
	else
	{
		dir = vec2_normalize(e->player_dist);
		dir.v = -3 * (e->height + e->width) * -dir.v;
		gfx->player.speed = vec3(dir.x, dir.y, e->height);
		gfx->player.nb_jump = 0;
		*hit = 1;
	}
}
