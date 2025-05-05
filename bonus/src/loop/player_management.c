/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:33:01 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/28 15:40:38 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "loop.h"
#include "map.h"
#include "collision.h"
#include <math.h>

/**
 * @brief Moves a position by a certain amount in a given direction.
 * 
 * @param pos Initial position.
 * @param add Amount to move.
 * @param angle Direction to move.
 * 
 * @return New position vector.
 */
static t_vec3	move_player(t_vec3 pos, float add, float angle)
{
	t_vec3	new_pos;

	new_pos.x = pos.x + add * cosf(angle);
	new_pos.y = pos.y + add * sinf(angle);
	new_pos.z = pos.z;
	return (new_pos);
}

static void	manage_sprint(t_gfx *gfx, t_vec3 last)
{
	t_vec3		move_dir;
	float		projected_speed;
	float		target_fov;
	const float	fov_speed = 10.0f;

	move_dir.v = gfx->player.pos.v - last.v;
	projected_speed = move_dir.x * gfx->player.dir.x
		+ move_dir.y * gfx->player.dir.y;
	target_fov = FOV * D2R;
	if (gfx->input.run)
		target_fov = FOV * D2R - projected_speed / gfx->dt / 100;
	gfx->fov += (target_fov - gfx->fov) * fov_speed * gfx->dt;
	gfx->tan_half_fov = tanf(gfx->fov / 2);
	gfx->screen_dist = 1.0f / (2.0f * gfx->tan_half_fov);
}

static void	player_collision(t_gfx *gfx, t_vec3 pos, t_vec3 last)
{
	check_map_collisions(gfx, &gfx->player, pos);
	if (check_entities_collisions(gfx, &gfx->player, -1) && !gfx->player.hit)
	{
		gfx->player.life_point -= 10;
		gfx->player.hit = 1;
		if (gfx->player.life_point <= 0)
		{
			gfx->player.is_dead = 1;
			toggle_level_end_screen(gfx, 1);
			return ;
		}
	}
	gfx->player.hit -= gfx->dt;
	if (gfx->player.hit < 0)
		gfx->player.hit = 0;
	if (vec2_length(gfx->player.plane_pos)
		> 2 * gfx->map.height + gfx->map.width)
		pos = last;
}

static void	player_move(t_gfx *gfx)
{
	t_vec3	pos;
	t_vec3	last;
	float	angle;
	float	new_pos;

	pos = gfx->player.pos;
	last = pos;
	angle = gfx->player.angle;
	new_pos = 2 * gfx->input.run + PLAYER_SPEED;
	gfx->player.dir = vec2(cosf(gfx->player.angle), sinf(gfx->player.angle));
	if (gfx->input.up)
		pos = move_player(pos, new_pos * gfx->dt, angle);
	if (gfx->input.left)
		pos = move_player(pos, new_pos * gfx->dt, angle - PI / 2);
	if (gfx->input.down)
		pos = move_player(pos, new_pos * gfx->dt, angle + PI);
	if (gfx->input.right)
		pos = move_player(pos, new_pos * gfx->dt, angle + PI / 2);
	gfx->player.speed.v += gfx->player.accel.v * gfx->dt;
	pos.v += gfx->player.speed.v * gfx->dt;
	player_collision(gfx, pos, last);
	if (gfx->game_vars.player_died)
		return ;
	manage_sprint(gfx, last);
	entity_check_if_pathfinding_should_be_refreshed(&gfx->player);
}

/**
 * @brief This function handles the input of the player.
 * 
 * @param gfx The main structure of the program.
 */
void	manage_player(t_gfx *gfx)
{
	t_tile	tile;
	t_vec2	tile_pos;
	t_point	p;

	if (gfx->input.cam_left)
		gfx->player.angle -= SPIN_SPEED * D2R * gfx->dt;
	if (gfx->input.cam_right)
		gfx->player.angle += SPIN_SPEED * D2R * gfx->dt;
	choose_gun_img(gfx);
	player_move(gfx);
	if (gfx->game_vars.player_died)
		return ;
	p = gfx->map.end_pos;
	tile = gfx->map.tile_data[p.y][p.x];
	tile_pos = gfx->player.plane_pos;
	tile_pos.v -= vec2((int)tile_pos.x, (int)tile_pos.y).v;
	if ((int)gfx->player.pos.x == p.x
		&& (int)gfx->player.pos.y == p.y
		&& (int)gfx->player.pos.z == tile.floor_height
		&& ((tile.door.orientation
				&& fabs(tile_pos.x - 0.5) < DOOR_THICKNESS)
			|| (!tile.door.orientation
				&& fabs(tile_pos.y - 0.5) < DOOR_THICKNESS)))
		toggle_level_end_screen(gfx, 0);
}
