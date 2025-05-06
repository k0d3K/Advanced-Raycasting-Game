/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:46:13 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 17:22:31 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "gfx.h"
#include <math.h>

void	set_player_variables(t_gfx *gfx)
{
	gfx->fov = FOV * D2R;
	gfx->tan_half_fov = tanf(gfx->fov / 2);
	gfx->screen_dist = 1.0f / (2.0f * gfx->tan_half_fov);
	gfx->time_elapsed = 0;
	gfx->player.life_point = 100;
	gfx->player.speed = vec3(0, 0, 0);
	gfx->player.accel = vec3(0, 0, 0);
	gfx->player.height = 1.0;
	gfx->player.width = 2 * COL_DIST;
	gfx->player.plane_pos
		= vec2(0.5f + gfx->map.start_pos.x, 0.5f + gfx->map.start_pos.y);
	gfx->player.pos.z = gfx->map.tile_data
	[gfx->map.start_pos.y][gfx->map.start_pos.x].floor_height + 2;
	if (gfx->player.pos.z > gfx->map.highest_wall)
		gfx->player.pos.z = gfx->map.highest_wall;
	gfx->player.angle = face_to_angle(gfx->map.start_orientation);
	gfx->gun.last_shot = get_time_micro();
	gfx->gun.nb_shot_left = FULL_MAGAZINE;
	gfx->game_vars.refresh_stats = 1;
}

int	init_resources(t_gfx *gfx)
{
	int	max_num_raycast;
	int	i;

	if (!pathfinding_init_resources(&gfx->pf_res, &gfx->map))
		return (0);
	max_num_raycast = (gfx->map.width + 1) * (gfx->map.height + 1);
	i = 0;
	while (i < N_THREADS)
	{
		gfx->render_threads[i].rcs_len = 0;
		gfx->render_threads[i].rcs
			= ft_calloc(max_num_raycast, sizeof(t_raycast_pair));
		if (!gfx->render_threads[i].rcs)
			return (0);
		i++;
	}
	return (1);
}
