/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hurt_effect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:33:52 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 14:45:49 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "gfx.h"

static inline t_color
	apply_hit_effect(float hit_value, int screen_x, int screen_y)
{
	t_vec2	center_p;
	t_vec2	d;
	float	center;
	float	dist;
	t_color	res;

	center_p.x = TRUE_WIN_W / 2.0f;
	center_p.y = WIN_H / 2.0f;
	d.x = screen_x - center_p.x;
	d.y = screen_y - center_p.y;
	dist = d.x * d.x + d.y * d.y;
	center = center_p.x * center_p.x + center_p.y * center_p.y;
	res = 0;
	if (dist > 0.6f * 0.6f * center)
	{
		dist = sqrtf(dist);
		center = sqrtf(center);
		res = ((uint8_t)
				(255 * hit_value * (dist - 0.6f * center) / (0.4f * center))
				<< 16);
	}
	return (res);
}

void	render_hurt_effect(t_gfx *gfx, int from, int to)
{
	t_color	*pxl;
	t_point	screen_coord;
	float	hit_value;

	hit_value = gfx->player.hit;
	if (hit_value < 0.01f)
		return ;
	pxl = gfx->hurt_img.data + from;
	screen_coord.y = 0;
	while (screen_coord.y < WIN_H)
	{
		screen_coord.x = from;
		while (screen_coord.x < to)
		{
			*pxl++
				= apply_hit_effect(hit_value, screen_coord.x, screen_coord.y);
			screen_coord.x++;
		}
		pxl = pxl + TRUE_WIN_W - (to - from);
		screen_coord.y++;
	}
}
