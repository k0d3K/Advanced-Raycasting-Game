/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:35:38 by dath              #+#    #+#             */
/*   Updated: 2025/04/29 19:27:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "gfx.h"

void	calculate_floor_ceil_ratios(
	t_gfx *gfx, t_raycast rc, t_vline_data *data)
{
	float	ceiling_height;
	float	floor_height;
	float	sum;
	float	cam_offset;

	cam_offset = rc.distance * gfx->sin_cam_dir;
	floor_height = rc.distance
		* gfx->tan_half_fov + rc.dist_from_ground
		- gfx->player.pos.z + cam_offset;
	ceiling_height = rc.distance
		* gfx->tan_half_fov - rc.dist_from_ground
		- rc.wall_height + gfx->player.pos.z - cam_offset;
	sum = ceiling_height + floor_height + rc.wall_height;
	data->ceil_ratio = ceiling_height / sum;
	data->floor_ratio = floor_height / sum;
	data->raw_floor_height = floor_height;
	data->raw_ceil_height = ceiling_height;
}

void	calculate_floor_ceil_heights(
		t_gfx *gfx, t_vline_data *data, int screen_x)
{
	int	ceil_height;
	int	floor_height;

	data->screen.x = screen_x;
	ceil_height = (int)(data->ceil_ratio * WIN_H);
	floor_height = (int)(data->floor_ratio * WIN_H);
	data->unclamped_ceil_height = ceil_height;
	data->unclamped_floor_height = floor_height;
	if (ceil_height < 0)
		ceil_height = 0;
	else if (ceil_height > WIN_H)
		ceil_height = WIN_H;
	if (floor_height < 0)
		floor_height = 0;
	else if (floor_height > WIN_H)
		floor_height = WIN_H;
	data->ceil_height = ceil_height;
	data->floor_height = floor_height;
	data->mid_screen = gfx->screen->data
		+ WIN_H * WIN_W / 2 + TRUE_WIN_W / 2;
}

void	draw_line(t_color *line, t_color *stop, t_color c)
{
	while (line + 16 * WIN_W <= stop)
	{
		line[0] = c;
		line[WIN_W] = c;
		line[2 * WIN_W] = c;
		line[3 * WIN_W] = c;
		line[4 * WIN_W] = c;
		line[5 * WIN_W] = c;
		line[6 * WIN_W] = c;
		line[7 * WIN_W] = c;
		line[8 * WIN_W] = c;
		line[9 * WIN_W] = c;
		line[10 * WIN_W] = c;
		line[11 * WIN_W] = c;
		line[12 * WIN_W] = c;
		line[13 * WIN_W] = c;
		line[14 * WIN_W] = c;
		line[15 * WIN_W] = c;
		line += 16 * WIN_W;
	}
	while (line != stop)
	{
		*line = c;
		line += WIN_W;
	}
}
