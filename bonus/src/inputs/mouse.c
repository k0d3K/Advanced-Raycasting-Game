/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:33:01 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 18:33:38 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "gfx.h"
#include <math.h>

/**
 * @brief This function calculates the time between two frames.
 * 
 * @param gfx The main structure of the program.
 * @param cam_initial The initial position of the camera.
 */
void	mouse_control(t_gfx *gfx, t_point cam_initial)
{
	t_point		cam_move;
	const float	mouse_sensibility = 5;

	mlx_mouse_get_pos(gfx->mlx, gfx->win, &cam_move.x, &cam_move.y);
	cam_move.p -= cam_initial.p;
	gfx->player.angle += (float)cam_move.x * gfx->dt / mouse_sensibility;
	gfx->cam_dir += (float)cam_move.y * gfx->dt / mouse_sensibility;
	if (cam_move.x != TRUE_WIN_W / 2 || cam_move.y != WIN_H / 2)
		mlx_mouse_move(gfx->mlx, gfx->win, TRUE_WIN_W / 2, WIN_H / 2);
	if (gfx->cam_dir < -PI / 4)
		gfx->cam_dir = -PI / 4;
	if (gfx->cam_dir > PI / 4)
		gfx->cam_dir = PI / 4;
	gfx->sin_cam_dir = sinf(gfx->cam_dir);
}

void	mouse_click(int button, int x, int y, t_gfx *gfx)
{
	t_vec2	dir;

	(void)x;
	(void)y;
	if (gfx->gun.reloading || gfx->gun.nb_shot_left == 0
		|| get_time_micro() - gfx->gun.last_shot < 200000)
		return ;
	gfx->gun.last_shot = get_time_micro();
	gfx->gun.n_gun_img = 1;
	gfx->gun.nb_shot_left--;
	if (!gfx->entity_hit || gfx->entity_hit->type != T_ENEMY)
		return ;
	if (button == 1 && gfx->entity_hit->speed.x + gfx->entity_hit->speed.y == 0)
	{
		gfx->entity_hit->life_point -= 30;
		dir = vec2_normalize(gfx->entity_hit->player_dist);
		dir.v = -dir.v * 3;
		gfx->entity_hit->speed = vec3(dir.x, dir.y, 2);
		if (gfx->entity_hit->life_point < 0)
		{
			gfx->entity_hit->is_dead = 1;
			gfx->game_vars.n_enemies_killed++;
		}
	}
}
