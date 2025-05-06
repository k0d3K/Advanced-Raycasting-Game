/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:54:13 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 17:13:08 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "raycast.h"
#include "gfx.h"
#include "utils.h"
#include <math.h>
#include <sys/cdefs.h>

/**
 * @brief Draw a line of pixels on the screen, with floor, cieling and wall.
 * 
 * @param gfx The graphics structure.
 * @param img The texture of the current cube
 * @param rcs First param is front raycast, second is back raycast.
 * @param screen_coord_x The x coordinate on the screen.
 * 
 * @note Need to add textures to walls.
 */
static void	draw_pixel_line(t_gfx *gfx, void *img, t_raycast rc, int screen_x)
{
	t_color			*data_end;
	t_vline_data	vline;
	t_color			*data_line;

	data_line = gfx->screen->data + screen_x;
	calculate_floor_ceil_ratios(gfx, rc, &vline);
	calculate_floor_ceil_heights(gfx, &vline, screen_x);
	vline.screen.y = vline.ceil_height;
	data_line += vline.ceil_height * WIN_W;
	data_end = data_line
		+ (WIN_H - vline.floor_height - vline.ceil_height) * WIN_W;
	if (data_end < data_line)
		return ;
	if (screen_x == TRUE_WIN_W / 2 && vline.mid_screen
		>= data_line && vline.mid_screen <= data_end)
		gfx->entity_hit = gfx->entity_drawn;
	vline.rc = rc;
	if (!rc.wall_face)
		draw_sprite((t_atlas *)img, vline, data_line, data_end);
	else
	{
		vline.n_faces_to_draw = rc.n_faces_visible;
		draw_cube((t_img *)img, vline, data_line, data_end);
	}
}

void	draw_entity_line(t_gfx *gfx, t_entity *e, t_raycast rc, int screen_x)
{
	int			begin;
	int			end;
	const float	fov_factor = gfx->tan_half_fov;

	begin = (int)((TRUE_WIN_W / 2) * (1 + (float)WIN_W / (2 * TRUE_WIN_W)
				* ((rc.dir.x - e->width / 2) / (rc.dir.y * fov_factor))));
	end = (int)((TRUE_WIN_W / 2) * (1 + (float)WIN_W / (2 * TRUE_WIN_W)
				* ((rc.dir.x + e->width / 2) / (rc.dir.y * fov_factor))));
	if (screen_x > begin && screen_x < end)
	{
		rc.wall_face = 0;
		rc.n_faces_visible = e->idx_anim;
		rc.distance = rc.dir.y;
		rc.x_ratio = (float)(screen_x - begin) / (end - begin);
		gfx->entity_drawn = e;
		draw_pixel_line(gfx, e->atlas, rc, screen_x);
	}
}

static void	draw_entities(t_gfx	*gfx, t_raycast_pair *rcs, int screen_coord_x)
{
	int			i;
	t_entity	*e;
	t_raycast	rc;
	float		dist_to_compare;

	i = gfx->entities.len;
	while (--i >= 0)
	{
		e = &gfx->entities.arr[i];
		if (!e->is_dead)
		{
			dist_to_compare = rcs->back.distance;
			rc.wall_height = e->height;
			rc.dist_from_ground = e->pos.z - rc.wall_height / 2 + 0.001;
			if (rcs->front.wall_height > rc.dist_from_ground
				|| rc.dist_from_ground > gfx->player.pos.z)
				dist_to_compare = rcs->front.distance;
			rc.dir.x = (-e->player_dist.y * gfx->player.dir.x
					+ e->player_dist.x * gfx->player.dir.y) / gfx->screen_dist;
			rc.dir.y = -e->player_dist.x * gfx->player.dir.x
				- e->player_dist.y * gfx->player.dir.y;
			if (rc.dir.y < dist_to_compare)
				draw_entity_line(gfx, e, rc, screen_coord_x);
		}
	}
}

static inline __attribute__ ((__always_inline__)) void	render_loop(
		t_gfx *gfx, t_raycast_pair *rcs, int screen_coord_x, float angle_x)
{
	float	fish_eye_corr;

	fish_eye_corr = cosf(angle_x - gfx->player.angle);
	rcs->front.distance *= fish_eye_corr;
	rcs->back.distance *= fish_eye_corr;
	rcs->front.inv_fish_eye_corr = 1.0f / fish_eye_corr;
	gfx->entity_drawn = NULL;
	{
		if (gfx->player.pos.z > rcs->front.wall_height)
			draw_top(gfx, *rcs, &gfx->textures.top, screen_coord_x);
		if (rcs->front.wall_height
			&& rcs->front.distance > 0 && rcs->front.n_faces_visible > 0)
			draw_pixel_line(gfx,
				get_face_image(rcs->front.wall_face, gfx),
				rcs->front, screen_coord_x);
	}
	draw_entities(gfx, rcs, screen_coord_x);
}

/**
 * @brief Renders the scene.
 * 
 * @param gfx The graphics structure.
 */
void	render(t_render_thread *rd, int from, int to)
{
	t_vec2	dir;
	float	angle_x;
	int		i;
	int		screen_coord_x;

	render_skybox(rd->gfx, from, to, rd->gfx->textures.sky);
	screen_coord_x = from;
	while (screen_coord_x < to)
	{
		angle_x = rd->gfx->player.angle + atanf((screen_coord_x
					- TRUE_WIN_W / 2) / (rd->gfx->screen_dist * WIN_H));
		dir = (t_vec2){{cosf(angle_x), sinf(angle_x)}};
		rd->rcs_len = 0;
		continuous_raycast(rd, dir);
		i = rd->rcs_len - 1;
		while (i >= 0)
		{
			render_loop(rd->gfx, rd->rcs + i, screen_coord_x, angle_x);
			i--;
		}
		screen_coord_x += 1;
	}
	render_hurt_effect(rd->gfx, from, to);
}
