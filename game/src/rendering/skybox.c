/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:26:17 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/29 19:27:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "gfx.h"

static void	precalculate_x_coords(
	int *buf,
	int from,
	float player_dir,
	int img_width)
{
	int			i;
	float		angle;

	i = 0;
	while (i < N_PIXEL_PER_SLICE)
	{
		angle = player_dir - (FOV / 2) * D2R
			+ ((float)from++ / TRUE_WIN_W) * (FOV * D2R);
		while (angle < 0)
			angle += 2 * PI;
		angle = fmodf(angle, 2 * PI);
		buf[i++] = img_width * (angle / (2 * PI));
	}
}

void	render_skybox(t_gfx *gfx, int from, int to, t_img tex)
{
	t_color	*pxl;
	t_point	screen_coord;
	int		i;
	int		cur_tex_y;
	int		angle_precalc[N_PIXEL_PER_SLICE];

	precalculate_x_coords(angle_precalc, from, gfx->player.angle, tex.size.x);
	screen_coord.y = 0;
	while (screen_coord.y < WIN_H)
	{
		screen_coord.x = from;
		i = 0;
		cur_tex_y = tex.size.y * (((PI / 2 + FOV * D2R) / 2 + gfx->cam_dir
					- FOV * D2R / 2 + FOV * D2R * screen_coord.y / WIN_H))
			/ (PI / 2 + FOV * D2R);
		cur_tex_y *= tex.size.x;
		pxl = gfx->screen->data + screen_coord.y * WIN_W + from;
		while (screen_coord.x < to)
		{
			*pxl++ = *(tex.data + cur_tex_y + angle_precalc[i++]);
			screen_coord.x++;
		}
		screen_coord.y++;
	}
}
