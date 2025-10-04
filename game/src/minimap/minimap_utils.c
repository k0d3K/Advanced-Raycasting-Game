/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:24:07 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:31:23 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include <math.h>
#include <string.h>

t_vec2	mmap_calc_pos_on_map(t_gfx *gfx, t_point minimap_pxl, t_vec2 dir)
{
	t_vec2		tmpf;
	t_vec2		local;

	local.x = ((float)minimap_pxl.x * MMAP_VIEW_WIDE) / MMAP_RADIUS;
	local.y = ((float)minimap_pxl.y * MMAP_VIEW_WIDE) / MMAP_RADIUS;
	if (MMAP_ROT)
	{
		tmpf.x = gfx->player.pos.x + dir.x * local.x - dir.y * local.y;
		tmpf.y = gfx->player.pos.y + dir.y * local.x + dir.x * local.y;
	}
	else
	{
		tmpf.x = gfx->player.pos.x + local.x;
		tmpf.y = gfx->player.pos.y + local.y;
	}
	return (tmpf);
}

t_point	map_calc_pos_on_mmap(t_gfx *gfx, t_entity entity)
{
	t_vec2	dir;
	t_vec2	tmpf;
	t_point	minimap_pxl;

	dir.x = cosf(gfx->player.angle + PI / 2);
	dir.y = sinf(gfx->player.angle + PI / 2);
	tmpf.x = entity.plane_pos.x - gfx->player.pos.x;
	tmpf.y = entity.plane_pos.y - gfx->player.pos.y;
	if (MMAP_ROT)
	{
		minimap_pxl.x = (int)((tmpf.x * dir.x + tmpf.y * dir.y)
				/ MMAP_VIEW_WIDE * MMAP_RADIUS);
		minimap_pxl.y = (int)((tmpf.y * dir.x - tmpf.x * dir.y)
				/ MMAP_VIEW_WIDE * MMAP_RADIUS);
	}
	else
	{
		minimap_pxl.x = (int)((tmpf.x * MMAP_VIEW_WIDE) / MMAP_RADIUS);
		minimap_pxl.y = (int)((tmpf.y * MMAP_VIEW_WIDE) / MMAP_RADIUS);
	}
	minimap_pxl.x += MMAP_RADIUS;
	minimap_pxl.y += MMAP_RADIUS;
	return (minimap_pxl);
}

static __always_inline
	t_color	average_neighbor_color(
		t_gfx *gfx, t_point pos, int n_pixels, int count)
{
	t_point		ij;
	int			argb[4];
	t_color		color;
	t_color		*data;

	memset(&argb, 0, sizeof(argb));
	data = gfx->back->data
		+ (pos.y - BLUR_FACTOR) * WIN_W + pos.x - BLUR_FACTOR;
	ij.y = n_pixels - 1;
	while (ij.y-- >= 0)
	{
		ij.x = n_pixels - 1;
		while (ij.x-- >= 0)
		{
			color = *data++;
			argb[0] += ((color >> 24) & 0xFF);
			argb[1] += ((color >> 16) & 0xFF);
			argb[2] += ((color >> 8) & 0xFF);
			argb[3] += (color & 0xFF);
		}
		data = data + WIN_W - n_pixels;
	}
	return ((argb[0] / count << 24) | (argb[1] / count << 16)
		| (argb[2] / count << 8) | argb[3] / count);
}

void	mmap_put_avg(t_gfx *gfx, t_point pos)
{
	t_color	c;
	t_color	*data;
	int		n_pixels;
	int		count;

	n_pixels = (BLUR_FACTOR * 2 + 1);
	count = n_pixels * n_pixels;
	c = average_neighbor_color(gfx, pos, n_pixels, count);
	data = gfx->minimap_img.data + pos.y * (MMAP_RADIUS * 2) + pos.x;
	*data = c;
}
