/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:54:13 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 18:30:11 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "raycast.h"
#include "config.h"
#include <math.h>

/**
 * @brief Draw the horizon line on the screen.
 * 
 * @param data_line The pointer of the first pixel of the line.
 */
static void	draw_horizon_line(t_gfx *gfx, t_color *data_line)
{
	const int	transition_pixel = PLAYER_EYE * WIN_Y;
	t_color		*first_stop;
	t_color		*second_stop;

	first_stop = data_line + transition_pixel * WIN_X;
	second_stop = data_line + WIN_Y * WIN_X;
	draw_line(data_line, first_stop, gfx->ceiling_col);
	draw_line(first_stop, second_stop, gfx->floor_col);
}

static inline __attribute__((always_inline))
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
	t_color	c;

	img_size = img->size;
	img_data = img->data + (int)(img_size.x * vline.rc.x_ratio);
	ypos = 0;
	if (vline.ceil_ratio < 0)
		ypos = -vline.raw_floor_height * img_size.y / WALL_HEIGHT;
	step = (float)img_size.y
		/ (WIN_Y - vline.unclamped_ceil_height - vline.unclamped_floor_height);
	while (data_line != data_end)
	{
		c = *(img_data + (int)ypos * img_size.x);
		ypos += step;
		*data_line = c;
		data_line += WIN_X;
	}
}

/**
 * @brief Draw a line of pixels on the screen, with floor, cieling and wall.
 * 
 * @param gfx The graphics structure.
 * @param img The texture of the current cube
 * @param rc The distance from the player to the wall.
 * @param screen_coord_x The x coordinate on the screen.
 * 
 * @note Need to add textures to walls.
 */
static void	draw_pixel_line(
	t_gfx *gfx,
	t_img *img,
	t_raycast rc,
	int screen_coord_x)
{
	t_color			*data_line;
	t_color			*data_end;
	t_vline_data	vline;

	calculate_floor_ceil_ratios(gfx, rc, &vline);
	calculate_floor_ceil_heights(&vline);
	data_line = gfx->screen->data + screen_coord_x;
	draw_line(data_line,
		data_line + vline.ceil_height * WIN_X, gfx->ceiling_col);
	draw_line(data_line + (WIN_Y - vline.floor_height) * WIN_X,
		data_line + WIN_Y * WIN_X, gfx->floor_col);
	data_line = data_line + vline.ceil_height * WIN_X;
	data_end = data_line
		+ (WIN_Y - vline.floor_height - vline.ceil_height) * WIN_X;
	vline.rc = rc;
	draw_cube(img, vline, data_line, data_end);
}

static inline __attribute__((always_inline))
	t_img	*get_cardinal_image(t_cardinal cardinal, t_gfx *gfx)
{
	t_img	*img;

	if (cardinal == NORTH)
		img = &gfx->textures.nord;
	else if (cardinal == SOUTH)
		img = &gfx->textures.south;
	else if (cardinal == WEST)
		img = &gfx->textures.west;
	else
		img = &gfx->textures.east;
	return (img);
}

/**
 * @brief Renders the scene.
 * 
 * @param gfx The graphics structure.
 */
void	render(t_gfx *gfx)
{
	int			screen_coord_x;
	float		angle_x;
	t_raycast	rc;
	t_vec2		dir;

	screen_coord_x = 0;
	while (screen_coord_x < WIN_X)
	{
		angle_x = gfx->player.dir + atanf((screen_coord_x
					- WIN_Y) / (gfx->screen_dist * WIN_X));
		dir = (t_vec2){{cosf(angle_x), sinf(angle_x)}};
		rc = raycast(gfx->player.pos, dir, gfx, gfx->max_raycast_distance);
		if (isnan(rc.distance))
			draw_horizon_line(gfx, gfx->screen->data + screen_coord_x);
		else
		{
			rc.distance *= cosf(angle_x - gfx->player.dir);
			draw_pixel_line(gfx,
				get_cardinal_image(rc.wall_face, gfx), rc, screen_coord_x);
		}
		screen_coord_x += 1;
	}
}
