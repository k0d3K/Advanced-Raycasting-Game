/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:54:22 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:31:28 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include <ctype.h>
#include <math.h>

static void	put_wall_pxl(t_gfx *gfx, t_point pos, t_vec2 map_pos)
{
	t_color	color;
	t_color	*data;
	int		heigth;
	int		gray;

	heigth = gfx->map.tile_data[(int)map_pos.y][(int)map_pos.x].floor_height;
	gray = (gfx->map.highest_wall - heigth) * 10;
	color = (0xFF << 24) | (gray << 16) | (gray << 8) | gray;
	data = gfx->minimap_img.data + pos.y * (MMAP_RADIUS * 2) + pos.x;
	*data = color;
}

static void	put_door_pxl(t_gfx *gfx, t_point minimap_pxl, t_vec2 map_pos)
{
	t_tile	tile;
	t_vec2	pos;

	tile = gfx->map.tile_data[(int)map_pos.y][(int)map_pos.x];
	if (!tile.door.orientation)
	{
		pos.x = map_pos.y - (int)map_pos.y;
		pos.y = map_pos.x - (int)map_pos.x;
	}
	else
	{
		pos.x = map_pos.x - (int)map_pos.x;
		pos.y = map_pos.y - (int)map_pos.y;
	}
	if (pos.x > 0.5 - DOOR_THICKNESS / 2 && pos.x < 0.5 + DOOR_THICKNESS / 2
		&& pos.y < 1 - tile.door.status)
		img_put(&gfx->minimap_img, minimap_pxl, GREEN);
	else if (tile.floor_height == 0)
		mmap_put_avg(gfx, minimap_pxl);
	else
		put_wall_pxl(gfx, minimap_pxl, map_pos);
}

static void	put_pxl_on_minimap(
	t_gfx *gfx, t_point minimap_pxl, t_vec2 dir)
{
	char	c;
	t_vec2	map_pos;

	map_pos = mmap_calc_pos_on_map(gfx, minimap_pxl, dir);
	minimap_pxl.p += MMAP_RADIUS;
	if (map_pos.x >= 0 && map_pos.y >= 0
		&& check_in_bounds(map_pos.x, map_pos.y, &gfx->map, &c))
	{
		if (isdigit(c) && c != '0')
			put_wall_pxl(gfx, minimap_pxl, map_pos);
		else if (c == 'D')
			put_door_pxl(gfx, minimap_pxl, map_pos);
		else
			mmap_put_avg(gfx, minimap_pxl);
	}
	else
		mmap_put_avg(gfx, minimap_pxl);
}

static void	draw_minimap_borders_once(t_img *minimap_img)
{
	static int	init = 0;
	t_point		pos;
	int			length;

	if (!init)
	{
		pos.y = -MMAP_RADIUS;
		while (pos.y <= MMAP_RADIUS)
		{
			pos.x = -MMAP_RADIUS;
			while (pos.x <= MMAP_RADIUS)
			{
				length = pos.x * pos.x + pos.y * pos.y;
				if (length < MMAP_RADIUS * MMAP_RADIUS
					&& length > (MMAP_RADIUS - 5) * (MMAP_RADIUS - 5))
					img_put(minimap_img,
						(t_point)(pos.p + MMAP_RADIUS), 0xFF333333);
				pos.x++;
			}
			pos.y++;
		}
		init = 1;
	}
}

void	render_map(t_gfx *gfx)
{
	t_point	minimap_pxl;
	int		length;
	t_vec2	dir;

	draw_minimap_borders_once(&gfx->minimap_img);
	dir.x = cosf(gfx->player.angle + PI / 2);
	dir.y = sinf(gfx->player.angle + PI / 2);
	minimap_pxl.y = -MMAP_RADIUS;
	while (minimap_pxl.y <= MMAP_RADIUS)
	{
		minimap_pxl.x = -MMAP_RADIUS;
		while (minimap_pxl.x <= MMAP_RADIUS)
		{
			length = minimap_pxl.x * minimap_pxl.x
				+ minimap_pxl.y * minimap_pxl.y;
			if (length <= (MMAP_RADIUS - 5) * (MMAP_RADIUS - 5))
				put_pxl_on_minimap(gfx, minimap_pxl, dir);
			minimap_pxl.x++;
		}
		minimap_pxl.y++;
	}
	mmap_draw_player(gfx);
	mmap_draw_entities(gfx, 0);
}
