/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_draw_faces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:08:05 by dath              #+#    #+#             */
/*   Updated: 2025/04/29 19:27:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "gfx.h"
#include <math.h>
#include <sys/cdefs.h>
#include <sys/param.h>

void	draw_cube(
	t_img *img,
	t_vline_data vline,
	t_color *data_line,
	t_color *data_end)
{
	float	ypos;
	float	step;
	t_point	img_size;
	t_color	*img_data;

	img_size = img->size;
	img_data = img->data + (int)(img_size.x * vline.rc.x_ratio);
	ypos = 0;
	if (vline.ceil_ratio < 0)
		ypos = -vline.raw_ceil_height * img_size.y;
	step = (float)img_size.y * vline.rc.wall_height
		/ (WIN_H - vline.unclamped_ceil_height - vline.unclamped_floor_height);
	while (data_line != data_end && vline.n_faces_to_draw > 0)
	{
		while (ypos >= img_size.y)
		{
			vline.n_faces_to_draw--;
			ypos -= img_size.y;
		}
		*data_line = *(img_data + (int)ypos * img_size.x);
		ypos += step;
		data_line += WIN_W;
		vline.screen.y += 1;
	}
}

// v.rc.n_faces_visible contains the index of the sprite
void	draw_sprite(
	t_atlas *atlas,
	t_vline_data v,
	t_color *data_line,
	t_color *data_end)
{
	float	ypos;
	float	step;
	t_color	*img_data;
	t_color	c;
	t_point	atlas_pos;

	atlas_pos = atlas_fetch(atlas, v.rc.n_faces_visible);
	img_data = atlas->img.data + atlas_pos.x + (int)(atlas->tile_width
			* v.rc.x_ratio) + (atlas->img.size.x * atlas_pos.y);
	ypos = 0;
	if (v.ceil_ratio < 0)
		ypos = -v.raw_ceil_height * atlas->tile_height / v.rc.wall_height;
	step = (float)atlas->tile_height
		/ (WIN_H - v.unclamped_ceil_height - v.unclamped_floor_height);
	while (data_line != data_end)
	{
		c = *(img_data + (int)ypos * atlas->img.size.x);
		ypos += step;
		if (c != 0)
			*data_line = c;
		data_line += WIN_W;
		v.screen.y += 1;
	}
}

static __always_inline void
	draw_top_calc_ratioes2(t_draw_top_vars *v, t_color *data_line)
{
	if (v->total_steps == 0)
		v->x_ratio_step = 1.0f;
	else
		v->x_ratio_step = 1.0f / v->total_steps;
	v->x_ratio = 1.0f;
	if (v->beg_line < data_line)
	{
		v->x_ratio -= ((data_line - v->beg_line) / WIN_W) * v->x_ratio_step;
		v->beg_line = data_line;
	}
}

static __always_inline void
	draw_top_calc_ratioes(t_gfx *gfx,
			t_raycast_pair rc_pair,
			t_draw_top_vars *v,
			t_color *data_line)
{
	float	l1;
	float	l2;
	t_color	*end_line;

	v->mid_screen = gfx->screen->data + WIN_H * WIN_W / 2 + TRUE_WIN_W / 2;
	v->true_height = gfx->player.pos.z - rc_pair.front.wall_height;
	l1 = gfx->screen_dist
		* (v->true_height / rc_pair.back.distance - gfx->sin_cam_dir);
	l2 = gfx->screen_dist
		* (v->true_height / rc_pair.front.distance - gfx->sin_cam_dir);
	v->total_steps = (l2 - l1) * WIN_H;
	end_line = data_line + WIN_H * WIN_W;
	v->beg_line = end_line;
	if (l1 <= 1)
		v->beg_line = data_line + ((int)(WIN_H / 2 + WIN_H * l1)) * WIN_W;
	v->stop_line = end_line;
	if (rc_pair.front.distance >= 0)
		v->stop_line = data_line + ((int)(WIN_H / 2 + WIN_H * l2)) * WIN_W;
	v->stop_line = MAX(v->stop_line, data_line);
	v->stop_line = MIN(v->stop_line, end_line);
	v->beg_line = MIN(v->beg_line, end_line);
	draw_top_calc_ratioes2(v, data_line);
}

void	draw_top(t_gfx *gfx,
	t_raycast_pair rc_pair,
	t_img *img,
	int screen_x)
{
	t_draw_top_vars	v;
	float			dist;
	t_vec2			pos;
	t_point			p;
	float			y_ratio;

	draw_top_calc_ratioes(gfx, rc_pair, &v, gfx->screen->data + screen_x);
	while (v.beg_line < v.stop_line)
	{
		if (v.beg_line == v.mid_screen)
			gfx->entity_hit = gfx->entity_drawn;
		y_ratio = v.x_ratio * rc_pair.front.distance
			/ (rc_pair.back.distance - v.x_ratio * (
					rc_pair.back.distance - rc_pair.front.distance));
		dist = rc_pair.front.distance
			+ y_ratio * (rc_pair.back.distance - rc_pair.front.distance);
		dist *= rc_pair.front.inv_fish_eye_corr;
		pos.v = gfx->player.plane_pos.v + rc_pair.front.dir.v * dist;
		p.x = (int)(img->size.x * fabsf(pos.x - (int)pos.x));
		p.y = (int)(img->size.y * fabsf(pos.y - (int)pos.y));
		*v.beg_line = *(img->data + img->size.x * p.y + p.x);
		v.beg_line += WIN_W;
		v.x_ratio -= v.x_ratio_step;
	}
}
