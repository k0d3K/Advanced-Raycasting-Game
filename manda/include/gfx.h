/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:57 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 18:00:02 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include "mlx.h"
# include "geo.h"
# include "img.h"
# include "texture.h"
# include "input.h"
# include "map.h"

typedef struct s_player
{
	t_vec2	pos;
	float	dir;
	float	height;
}	t_player;

typedef struct s_gfx
{
	void		*mlx;
	void		*win;
	t_img		screen1;
	t_img		screen2;
	float		screen_dist;
	t_img		*screen;
	t_img		*back;
	t_textures	textures;
	float		dt;
	float		tan_half_fov;
	float		max_raycast_distance;

	t_player	player;
	t_input		input;
	t_map		map;

	char		*texture_files[4];
	t_color		floor_col;
	t_color		ceiling_col;
}	t_gfx;

int		gfx_init(t_gfx *gfx);
void	gfx_deinit(t_gfx *gfx);
void	gfx_put(t_gfx *gfx, t_point p, t_color c);
void	gfx_render(t_gfx *gfx);

typedef struct s_bresenham
{
	t_point	from;
	t_point	to;
	t_point	dir;
	t_point	sign;
	int		err;
	int		e2;
}	t_bresenham;

void	gfx_line(t_gfx *gfx, t_point from, t_point to, t_color c);

void	loop(t_gfx *gfx);

#endif
