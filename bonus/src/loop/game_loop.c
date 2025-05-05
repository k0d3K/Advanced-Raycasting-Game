/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:15:49 by dath              #+#    #+#             */
/*   Updated: 2025/04/26 18:20:28 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>

static void	do_render(t_gfx *gfx)
{
	gfx->max_raycast_distance = vec2_length(gfx->player.plane_pos) + sqrtf
		(gfx->map.height * gfx->map.height + gfx->map.width * gfx->map.width);
	pthread_cond_broadcast(&gfx->render_cond);
	wait_until_all_slices_rendered(gfx);
}

void	game_loop(t_gfx *gfx)
{
	t_point	cam_initial;

	mlx_mouse_get_pos(gfx->mlx, gfx->win, &cam_initial.x, &cam_initial.y);
	debug_clear_window(gfx);
	manage_doors(gfx, 0, 0);
	manage_player(gfx);
	if (gfx->game_vars.game_state != PLAYING)
		return ;
	manage_entities(gfx);
	if (gfx->game_vars.game_state != PLAYING)
		return ;
	debug_render_map(gfx);
	gfx->max_raycast_distance = vec2_length(gfx->player.plane_pos) + sqrtf
		(gfx->map.height * gfx->map.height + gfx->map.width * gfx->map.width);
	do_render(gfx);
	gfx_render(gfx);
	mlx_put_image_to_window(gfx->mlx, gfx->win, gfx->minimap_img.mlx_img, 0, 0);
	mlx_put_image_to_window(gfx->mlx, gfx->win, gfx->stats_img.mlx_img, 0, 0);
	if (gfx->player.hit >= 0.01f)
		mlx_put_image_to_window(
			gfx->mlx, gfx->win, gfx->hurt_img.mlx_img, 0, 0);
	debug_render_map_post(gfx);
	mouse_control(gfx, cam_initial);
}
