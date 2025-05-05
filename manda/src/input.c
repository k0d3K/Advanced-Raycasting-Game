/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:33:01 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/18 18:34:55 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "gfx.h"

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
	else if (keycode == XK_Right)
		gfx->input.cam_right = 1;
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
	else if (keycode == XK_Escape)
		mlx_loop_end(gfx->mlx);
}
