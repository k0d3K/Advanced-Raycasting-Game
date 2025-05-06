/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_life_bar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:54:22 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 18:54:24 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "gfx.h"

static int	get_bar_color(t_drawing d, float life_percent, int pos_y)
{
	int		red;
	int		green;
	int		color;
	float	brightness;

	brightness = 1.0f - 0.8f * (float)pos_y / d.size.y;
	if (life_percent > 0.5f)
	{
		red = (int)((1.0f - life_percent) * 2.0f * 255);
		green = 255;
	}
	else
	{
		red = 255;
		green = (int)(life_percent * 2.0f * 255);
	}
	red *= brightness;
	green *= brightness;
	color = (0xFF << 24) | (red << 16) | (green << 8);
	return (color);
}

static void	draw_circle(
		t_gfx *gfx, t_point minimap_pxl, t_point center, t_drawing d)
{
	t_point	pos;
	float	dist;
	int		value;
	int		color;

	minimap_pxl.p += d.pos.p;
	pos.p = minimap_pxl.p - center.p;
	dist = pos.x * pos.x + pos.y * pos.y;
	if (dist <= d.radius * d.radius)
	{
		if (dist > (d.radius - d.thick) * (d.radius - d.thick))
		{
			value = 100 * (1.0f - (float)(pos.y + d.radius) / d.size.y);
			color = (0xFF << 24) | (value << 16) | (value << 8) | value;
		}
		else if ((minimap_pxl.x - d.pos.x) * 100 / d.size.x
			< gfx->player.life_point)
			color = get_bar_color(d, (float)gfx->player.life_point / 100,
					pos.y + d.radius);
		else
			return ;
		img_put(&gfx->stats_img, minimap_pxl, color);
	}
}

static void	draw_rectangle(t_gfx *gfx, t_drawing d, t_point minimap_pxl)
{
	int	value;
	int	color;

	if (minimap_pxl.y < d.thick || minimap_pxl.y > d.size.y - d.thick)
	{
		value = 100 * (1.0f - (float)minimap_pxl.y / d.size.y);
		color = (0xFF << 24) | (value << 16) | (value << 8) | value;
	}
	else if ((float)minimap_pxl.x / (d.size.x)
		< (float)gfx->player.life_point / 100)
		color = get_bar_color(d, (float)gfx->player.life_point / 100,
				minimap_pxl.y);
	else
		return ;
	minimap_pxl.p += d.pos.p;
	img_put(&gfx->stats_img, minimap_pxl, color);
}

static void	config_life_bar(t_drawing *life_bar)
{
	life_bar->pos.x = 0.8f * TRUE_WIN_W;
	life_bar->pos.y = 0.9f * WIN_H;
	life_bar->size.x = 200 * TRUE_WIN_W / WIN_W;
	life_bar->size.y = 30;
	life_bar->thick = 3;
	life_bar->radius = life_bar->size.y / 2;
}

void	render_life_bar(t_gfx *gfx)
{
	t_drawing	d;
	t_point		minimap_pxl;

	config_life_bar(&d);
	minimap_pxl.y = 0;
	while (minimap_pxl.y < d.size.y)
	{
		minimap_pxl.x = 0;
		while (minimap_pxl.x < d.size.x)
		{
			if (minimap_pxl.x < d.radius)
				draw_circle(gfx, minimap_pxl, point(d.pos.x + d.radius,
						d.pos.y + d.radius), d);
			else if (minimap_pxl.x > d.size.x - d.radius)
				draw_circle(gfx, minimap_pxl, point(d.pos.x + d.size.x
						- d.radius, d.pos.y + d.radius), d);
			else
				draw_rectangle(gfx, d, minimap_pxl);
			minimap_pxl.x++;
		}
		minimap_pxl.y++;
	}
	draw_heart(gfx, d);
	draw_bullets(gfx, d);
}
