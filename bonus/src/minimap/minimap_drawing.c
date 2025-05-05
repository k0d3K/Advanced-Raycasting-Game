/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:24:07 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:31:14 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static __always_inline void	calculate_point_size(
	float *entity_size, float *circle_limit, t_entity entity)
{
	float	z;
	float	size;

	z = entity.pos.z / 3;
	size = (float)MMAP_RADIUS * entity.width / 2
		/ MMAP_VIEW_WIDE *(1 + sqrtf(z)) + entity.height / 2;
	*circle_limit = (size - (size / 5))
		* (size - (size / 5));
	*entity_size = size;
}

void	mmap_draw_player(t_gfx *gfx)
{
	t_point		minimap_pxl;
	int			length;
	float		player_size;
	float		circle_limit;

	calculate_point_size(&player_size, &circle_limit, gfx->player);
	minimap_pxl.y = -(int)player_size + MMAP_RADIUS;
	while (minimap_pxl.y <= (int)player_size + MMAP_RADIUS)
	{
		minimap_pxl.x = -(int)player_size + MMAP_RADIUS;
		while (minimap_pxl.x <= (int)player_size + MMAP_RADIUS)
		{
			length = (minimap_pxl.x - MMAP_RADIUS)
				* (minimap_pxl.x - MMAP_RADIUS)
				+ (minimap_pxl.y - MMAP_RADIUS)
				* (minimap_pxl.y - MMAP_RADIUS);
			if (length < circle_limit)
				img_put(&gfx->minimap_img, minimap_pxl, WHITE);
			else if (length < player_size * player_size)
				img_put(&gfx->minimap_img, minimap_pxl, BLACK);
			minimap_pxl.x++;
		}
		minimap_pxl.y++;
	}
}

static void	mmap_draw_entity(t_gfx *gfx, t_point mpos,
	float entity_size, float circle_limit)
{
	t_point	minimap_pxl;
	t_point	p;
	int		length;

	minimap_pxl.y = mpos.y - entity_size;
	while (minimap_pxl.y <= mpos.y + entity_size)
	{
		minimap_pxl.x = mpos.x - entity_size;
		while (minimap_pxl.x <= mpos.x + entity_size)
		{
			p.p = minimap_pxl.p - point(1, 1).p * MMAP_RADIUS;
			if (p.x * p.x + p.y * p.y <= (MMAP_RADIUS - 5) * (MMAP_RADIUS - 5))
			{
				p.p = minimap_pxl.p - mpos.p;
				length = p.x * p.x + p.y * p.y;
				if (length < circle_limit)
					img_put(&gfx->minimap_img, minimap_pxl, RED);
				else if (length < entity_size * entity_size)
					img_put(&gfx->minimap_img, minimap_pxl, BLACK);
			}
			minimap_pxl.x++;
		}
		minimap_pxl.y++;
	}
}

void	mmap_draw_entities(t_gfx *gfx, unsigned int i)
{
	int			length;
	t_point		mpos;
	float		size;
	float		circle_limit;
	t_entity	e;

	while (i < gfx->entities.len)
	{
		e = gfx->entities.arr[i];
		if (!e.is_dead && e.type == T_ENEMY)
		{
			calculate_point_size(&size, &circle_limit, e);
			mpos = map_calc_pos_on_mmap(gfx, e);
			length = (mpos.x - MMAP_RADIUS) * (mpos.x - MMAP_RADIUS)
				+ (mpos.y - MMAP_RADIUS) * (mpos.y - MMAP_RADIUS);
			if (length <= (MMAP_RADIUS - 5 + size) * (MMAP_RADIUS - 5 + size))
				mmap_draw_entity(gfx, mpos, size, circle_limit);
			length = vec2_length((t_vec2)
					(e.plane_pos.v - gfx->player.plane_pos.v));
			if (gfx->player.pos.z > e.pos.z
				&& length < (e.width + gfx->player.width) / 2)
				mmap_draw_player(gfx);
		}
		i++;
	}
}
