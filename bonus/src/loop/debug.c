/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:34:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/29 19:27:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include <stdio.h>

#ifdef DEBUG

static void	draw_square(t_gfx *gfx, int x, int y)
{
	const t_point	top_right = point(x + UI_SCALE, y);
	const t_point	bottom_right = point(x + UI_SCALE, y + UI_SCALE);
	const t_point	bottom_left = point(x, y + UI_SCALE);
	const t_color	sq_col = RED;
	const t_point	p = point(x, y);

	gfx_line(gfx, p, top_right, sq_col);
	gfx_line(gfx, top_right, bottom_right, sq_col);
	gfx_line(gfx, p, bottom_left, sq_col);
	gfx_line(gfx, bottom_left, bottom_right, sq_col);
}

void	debug_clear_window(t_gfx *gfx)
{
	int		x;
	int		y;
	t_color	*data;

	data = gfx->screen->data + TRUE_WIN_W;
	y = WIN_H;
	while (--y >= 0)
	{
		x = TRUE_WIN_W;
		while (--x >= 0)
			*data++ = BLACK;
		data += TRUE_WIN_W;
	}
}

void	debug_render_map(t_gfx *gfx)
{
	int		x;
	int		y;

	y = gfx->map.height;
	while (--y >= 0)
	{
		x = gfx->map.width;
		while (--x >= 0)
		{
			if (gfx->map.tile_data[y][x].floor_height > 0)
				draw_square(gfx, TRUE_WIN_W + x * UI_SCALE, y * UI_SCALE);
		}
	}
}

void	debug_render_map_post(t_gfx *gfx)
{
	int		x;
	int		y;
	t_point	screen_pos;
	char	buf[5];

	y = 0;
	while (y < gfx->map.height)
	{
		x = 0;
		while (x < gfx->map.width)
		{
			snprintf(buf, 5, "%d", gfx->map.tile_data[y][x].floor_height);
			screen_pos.x = TRUE_WIN_W + x * UI_SCALE + UI_SCALE / 2;
			screen_pos.y = y * UI_SCALE + UI_SCALE / 2;
			(void)screen_pos;
			mlx_string_put(gfx->mlx, gfx->win,
				screen_pos.x, screen_pos.y, WHITE, buf);
			x++;
		}
		y++;
	}
}

#endif
