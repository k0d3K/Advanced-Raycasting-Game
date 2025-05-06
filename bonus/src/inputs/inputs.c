/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:33:01 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 15:19:49 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "gfx.h"
#include "map.h"

static int	verify_ending(t_gfx *gfx)
{
	return (gfx->game_vars.n_coins_collected == gfx->game_vars.n_coins
		&& gfx->game_vars.n_enemies_killed == gfx->game_vars.n_enemies);
}

static void	action_door(t_gfx *gfx, float i)
{
	t_tile	tail;
	t_vec2	pos;
	t_door	*door;

	while (i < 3)
	{
		pos.v = gfx->player.plane_pos.v + (float)i * gfx->player.dir.v;
		if (pos.x < 0 || pos.y < 0
			|| !check_in_bounds((int)pos.x, (int)pos.y, &gfx->map, NULL))
			return ;
		tail = gfx->map.tile_data[(int)pos.y][(int)pos.x];
		if (tail.type == T_DOOR && tail.door.height > gfx->player.pos.z)
		{
			if ((int)pos.x == gfx->map.end_pos.x
				&& (int)pos.y == gfx->map.end_pos.y && !verify_ending(gfx))
					return ;
			door = &gfx->map.tile_data[(int)pos.y][(int)pos.x].door;
			if (door->state >= OPENING)
				door->state = CLOSING;
			else
				door->state = OPENING;
			break ;
		}
		i += 1;
	}
}

void	on_press(int keycode, t_gfx *gfx)
{
	if (keycode == XK_a)
		gfx->input.left = 1;
	else if (keycode == XK_w)
		gfx->input.up = 1;
	else if (keycode == XK_s)
		gfx->input.down = 1;
	else if (keycode == XK_d)
		gfx->input.right = 1;
	else if (keycode == XK_Left)
		gfx->input.cam_left = 1;
	else if (keycode == XK_Up)
		gfx->input.cam_up = 1;
	else if (keycode == XK_Down)
		gfx->input.cam_down = 1;
	else if (keycode == XK_Right)
		gfx->input.cam_right = 1;
	else if (keycode == XK_space && gfx->player.nb_jump < 2)
	{
		gfx->player.speed.z = 3 / (1 + gfx->player.nb_jump / 2);
		gfx->player.nb_jump += 1;
	}
	else if (keycode == XK_e && gfx->game_vars.game_state == PLAYING)
		action_door(gfx, 0.5f);
	else if (keycode == XK_Shift_L)
		gfx->input.run = 1;
}

void	on_release2(int keycode, t_gfx *gfx)
{
	if (keycode == XK_r)
	{
		gfx->gun.reloading = 1;
		gfx->gun.n_gun_img = 3;
		gfx->gun.last_shot = get_time_micro();
	}
	else if (keycode == XK_Escape)
		mlx_loop_end(gfx->mlx);
	else if (keycode == XK_Shift_L)
		gfx->input.run = 0;
	else if (keycode == XK_Return)
		gfx->input.level_select_confirm = 1;
}

void	on_release(int keycode, t_gfx *gfx)
{
	if (keycode == XK_a)
		gfx->input.left = 0;
	else if (keycode == XK_w)
		gfx->input.up = 0;
	else if (keycode == XK_s)
		gfx->input.down = 0;
	else if (keycode == XK_d)
		gfx->input.right = 0;
	else if (keycode == XK_Left)
		gfx->input.cam_left = 0;
	else if (keycode == XK_Right)
		gfx->input.cam_right = 0;
	else if (keycode == XK_Up)
	{
		gfx->input.cam_up = 0;
		gfx->input.level_select_up = 1;
	}
	else if (keycode == XK_Down)
	{
		gfx->input.cam_down = 0;
		gfx->input.level_select_down = 1;
	}
	else
		on_release2(keycode, gfx);
}
