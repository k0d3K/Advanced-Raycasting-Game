/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:34:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:42:43 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "loop.h"
#include "rendering.h"
#include "map.h"
#include "collision.h"
#include <pthread.h>
#include <sys/param.h>

void	manage_doors(t_gfx *gfx, int x, int y)
{
	t_door	*door;

	while (y < gfx->map.height)
	{
		x = -1;
		while (++x < gfx->map.width)
		{
			if (gfx->map.tile_data[y][x].type != T_DOOR)
				continue ;
			door = &gfx->map.tile_data[y][x].door;
			door->status += gfx->dt * (door->state == OPENING);
			door->status -= gfx->dt * (door->state == CLOSING);
			if (door->status >= 0.9)
			{
				door->state = OPENED;
				door->status = 0.9;
			}
			else if (door->status <= 0)
			{
				door->state = CLOSED;
				door->status = 0;
			}
		}
		y++;
	}
}

static void	entity_stupid_ai(t_gfx *gfx, int i)
{
	t_vec3	last;
	t_vec3	pos;

	pathfinding_calc_path(gfx, &gfx->entities.arr[i]);
	gfx->entities.arr[i].speed.v += gfx->entities.arr[i].accel.v * gfx->dt;
	pos = gfx->entities.arr[i].pos;
	last = pos;
	pos.v += gfx->entities.arr[i].speed.v * gfx->dt;
	if (gfx->entities.arr[i].can_reach_player)
	{
		pos.x += gfx->entities.arr[i].dir.x * 1.2f * gfx->dt;
		pos.y += gfx->entities.arr[i].dir.y * 1.2f * gfx->dt;
	}
	check_map_collisions(gfx, &gfx->entities.arr[i], pos);
	check_entities_collisions(gfx, &gfx->entities.arr[i], i);
	pos = gfx->entities.arr[i].pos;
	if (vec3_length((t_vec3)(last.v - pos.v)) < 0.002
		&& vec3_length(gfx->entities.arr[i].accel) < 0.002)
		gfx->entities.arr[i].speed.z = 4 + gfx->entities.arr[i].height;
}

void	manage_entities(t_gfx *gfx)
{
	unsigned int	i;
	static float	a = 0;

	i = 0;
	a += gfx->dt;
	while (i < gfx->entities.len)
	{
		if (a >= 0.07f && gfx->entities.arr[i].type == T_COIN)
			gfx->entities.arr[i].idx_anim++;
		if (!gfx->entities.arr[i].is_dead
			&& gfx->entities.arr[i].type == T_ENEMY)
			entity_stupid_ai(gfx, i);
		i++;
	}
	if (a >= 0.07f)
		a = 0;
	sort_entities_by_dist(gfx, gfx->player.plane_pos);
}
