/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:35:38 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 15:57:01 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "config.h"

void	calculate_floor_ceil_ratios(
	t_gfx *gfx, t_raycast rc, t_vline_data *data)
{
	float	ceiling_height;
	float	floor_height;
	float	sum;

	ceiling_height = rc.distance
		* (float)WIN_Y / WIN_X * gfx->tan_half_fov - gfx->player.height;
	floor_height = rc.distance
		* (float)WIN_Y / WIN_X * gfx->tan_half_fov
		- WALL_HEIGHT + gfx->player.height;
	sum = ceiling_height + floor_height + WALL_HEIGHT;
	data->ceil_ratio = floor_height / sum;
	data->floor_ratio = ceiling_height / sum;
	data->raw_floor_height = floor_height;
	data->raw_ceil_height = ceiling_height;
}

void	calculate_floor_ceil_heights(t_vline_data *data)
{
	int	ceil_height;
	int	floor_height;

	ceil_height = (int)(data->ceil_ratio * WIN_Y);
	floor_height = (int)(data->floor_ratio * WIN_Y);
	data->unclamped_ceil_height = ceil_height;
	data->unclamped_floor_height = floor_height;
	if (ceil_height < 0)
		ceil_height = 0;
	else if (ceil_height > WIN_Y / 2)
		ceil_height = WIN_Y / 2;
	if (floor_height < 0)
		floor_height = 0;
	else if (floor_height > WIN_Y / 2)
		floor_height = WIN_Y / 2;
	data->ceil_height = ceil_height;
	data->floor_height = floor_height;
}

void	draw_line(t_color *line, t_color *stop, t_color c)
{
	while (line + 16 * WIN_X <= stop)
	{
		line[0] = c;
		line[WIN_X] = c;
		line[2 * WIN_X] = c;
		line[3 * WIN_X] = c;
		line[4 * WIN_X] = c;
		line[5 * WIN_X] = c;
		line[6 * WIN_X] = c;
		line[7 * WIN_X] = c;
		line[8 * WIN_X] = c;
		line[9 * WIN_X] = c;
		line[10 * WIN_X] = c;
		line[11 * WIN_X] = c;
		line[12 * WIN_X] = c;
		line[13 * WIN_X] = c;
		line[14 * WIN_X] = c;
		line[15 * WIN_X] = c;
		line += 16 * WIN_X;
	}
	while (line != stop)
	{
		*line = c;
		line += WIN_X;
	}
}
