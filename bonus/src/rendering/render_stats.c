/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:54:22 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/04 18:21:33 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "libft.h"
#include <ctype.h>
#include <math.h>

#define B_SIZE_X	20
#define B_SIZE_Y	20
#define H_SIZE_X	50
#define H_SIZE_Y	50
#define GUN_SIZE_X	650
#define GUN_SIZE_Y	800
#define CROSS_RAD	12
#define CROSS_THICK	2
#define CROSS_COLOR	0xFF000000

void	draw_heart(t_gfx *gfx, t_drawing d)
{
	t_point	heart_pxl;
	t_point	img_pxl;
	t_point	put_pxl;
	t_color	color;

	heart_pxl.y = 0;
	while (heart_pxl.y < H_SIZE_Y)
	{
		heart_pxl.x = 0;
		while (heart_pxl.x < H_SIZE_X)
		{
			img_pxl.p = heart_pxl.p * gfx->textures.heart.size.p
				/ point(H_SIZE_X, H_SIZE_Y).p;
			color = img_get(&gfx->textures.heart, img_pxl);
			put_pxl.p = point(d.pos.x - d.size.y / 2 - H_SIZE_X / 3,
					d.pos.y + d.size.y / 2 - H_SIZE_Y / 2).p + heart_pxl.p;
			if (color != 0)
				img_put(&gfx->stats_img, put_pxl, color);
			heart_pxl.x++;
		}
		heart_pxl.y++;
	}
}

void	draw_bullets(t_gfx *gfx, t_drawing d)
{
	t_point	bullet_pxl;
	t_point	img_pxl;
	t_color	color;
	int		i;

	i = -1;
	while (++i < gfx->gun.nb_shot_left)
	{
		bullet_pxl.y = -1;
		while (++bullet_pxl.y < B_SIZE_Y)
		{
			bullet_pxl.x = -1;
			while (++bullet_pxl.x < B_SIZE_X)
			{
				img_pxl.p = bullet_pxl.p * gfx->textures.bullet.size.p
					/ point(B_SIZE_X, B_SIZE_Y).p;
				color = img_get(&gfx->textures.bullet, img_pxl);
				img_pxl.p = point(d.pos.x + d.size.y / 2 + i * B_SIZE_X,
						d.pos.y - d.size.y / 2 - B_SIZE_Y).p + bullet_pxl.p;
				if (color != 0)
					img_put(&gfx->stats_img, img_pxl, color);
			}
		}
	}
}

static void	draw_gun(t_gfx *gfx)
{
	t_point	gun_pxl;
	t_point	put_pxl;
	t_color	color;
	t_point	atlas_pos;

	gun_pxl.y = 0;
	while (gun_pxl.y < GUN_SIZE_Y)
	{
		gun_pxl.x = 0;
		while (gun_pxl.x < GUN_SIZE_X)
		{
			atlas_pos = atlas_fetch(&gfx->textures.gun, gfx->gun.n_gun_img);
			put_pxl.p = gun_pxl.p * point(gfx->textures.gun.tile_width,
					gfx->textures.gun.tile_height).p
				/ point(GUN_SIZE_X, GUN_SIZE_Y).p + atlas_pos.p;
			color = *(gfx->textures.gun.img.data + (int)put_pxl.y
					* gfx->textures.gun.img.size.x + (int)put_pxl.x);
			put_pxl.p = point(TRUE_WIN_W / 2 - GUN_SIZE_X / 2,
					WIN_H - GUN_SIZE_Y).p + gun_pxl.p;
			if (color != 0)
				img_put(&gfx->stats_img, put_pxl, color);
			gun_pxl.x++;
		}
		gun_pxl.y++;
	}
}

static void	draw_crosshair(t_gfx *gfx)
{
	const int		branche = CROSS_RAD / 4;
	const t_point	c = point(gfx->stats_img.size.x / 2,
			gfx->stats_img.size.y / 2);
	float			dist;
	int				x;
	int				y;

	y = -CROSS_RAD - CROSS_THICK - branche;
	while (y <= CROSS_RAD + CROSS_THICK + branche)
	{
		x = -CROSS_RAD - CROSS_THICK - branche;
		while (x <= CROSS_RAD + CROSS_THICK + branche)
		{
			dist = sqrtf(x * x + y * y);
			if ((dist >= CROSS_RAD && dist <= CROSS_RAD + CROSS_THICK)
				|| (abs(x) < CROSS_THICK && abs(y) > CROSS_RAD - 2 * branche)
				|| (abs(y) < CROSS_THICK && abs(x) > CROSS_RAD - 2 * branche)
				|| x * x + y * y <= CROSS_THICK * CROSS_THICK)
				img_put(&gfx->stats_img, point(c.x + x, c.y + y), CROSS_COLOR);
			x++;
		}
		y++;
	}
}

void	render_stats(t_gfx *gfx)
{
	static int	last_player_life = 0;
	static int	last_gun_img = 0;

	if (gfx->player.life_point != last_player_life
		|| gfx->gun.n_gun_img != last_gun_img)
	{
		last_gun_img = gfx->gun.n_gun_img;
		last_player_life = gfx->player.life_point;
		clear_img(&gfx->stats_img, 0);
		render_life_bar(gfx);
		draw_crosshair(gfx);
		draw_gun(gfx);
	}
}
