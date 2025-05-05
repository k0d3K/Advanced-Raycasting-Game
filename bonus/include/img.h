/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:21:06 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/26 18:13:45 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# include "geo.h"
# include <stdint.h>

typedef unsigned int	t_color;

# define GREEN	0xFF00FF00
# define RED	0xFFFF0000
# define BLUE	0xFF0000FF
# define WHITE	0xFFFFFFFF
# define BLACK	0xFF000000
# define YELLOW	0xFFFFFF00
# define PINK	0xFFFF00FF
# define CYAN	0xFF00FFFF

typedef struct s_img
{
	t_color	*data;
	t_point	size;
	void	*mlx_img;
}	t_img;

typedef struct s_gfx	t_gfx;

int		img_init(t_gfx *gfx, t_img *img, t_point size);
void	img_put(t_img *img, t_point p, t_color c);
t_color	img_get(t_img *img, t_point p);

void	clear_img(t_img *img, t_color clear_color);

typedef struct s_atlas
{
	t_img		img;
	int32_t		n_rows;
	int32_t		n_columns;
	int32_t		tile_width;
	int32_t		tile_height;
	int32_t		n_tiles;
}	t_atlas;

char	*atlas_init(t_gfx *gfx, t_atlas *atlas,
			char *filename, t_point n_textures);
t_point	atlas_fetch(t_atlas *atlas, int32_t n);
void	atlas_render(t_atlas *atlas, t_img *out, int32_t n, t_point p);

#endif