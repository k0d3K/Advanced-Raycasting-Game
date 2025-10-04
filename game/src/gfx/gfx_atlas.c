/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_atlas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:11:59 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/16 20:26:24 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "img.h"
#include "bitmap.h"
#include <assert.h>

char	*atlas_init(t_gfx *gfx, t_atlas *atlas,
	char *filename, t_point n_textures)
{
	char	*err;

	assert(n_textures.x > 0 && n_textures.y > 0);
	err = bitmap_load(gfx, &atlas->img, filename);
	if (err)
		return (err);
	atlas->n_columns = n_textures.x;
	atlas->n_rows = n_textures.y;
	atlas->tile_width = atlas->img.size.x / atlas->n_columns;
	atlas->tile_height = atlas->img.size.y / atlas->n_rows;
	atlas->n_tiles = atlas->n_rows * atlas->n_columns;
	return (NULL);
}

t_point	atlas_fetch(t_atlas *atlas, int32_t n)
{
	t_point	res;

	n %= atlas->n_tiles;
	res.x = n % atlas->n_columns;
	res.y = n / atlas->n_columns;
	if (res.x >= atlas->n_columns || res.x < 0)
		res.x = 0;
	if (res.y >= atlas->n_rows || res.y < 0)
		res.y = 0;
	res.x *= atlas->tile_width;
	res.y *= atlas->tile_height;
	return (res);
}

static void	atlas_hline(t_atlas *atlas, t_color *img_data, t_color *tile_data)
{
	t_color		c;
	uint32_t	i;
	uint32_t	width;

	i = 0;
	width = atlas->tile_width;
	while (i < width)
	{
		c = *tile_data++;
		if (c)
			*img_data = c;
		img_data++;
		i++;
	}
}

void	atlas_render(t_atlas *atlas, t_img *out, int32_t n, t_point p)
{
	t_point		atlas_pos;
	uint32_t	y;
	uint32_t	height;
	t_color		*tile_data;
	t_color		*img_data;

	atlas_pos = atlas_fetch(atlas, n);
	if (p.x < 0 || p.x + atlas->tile_width > out->size.x
		|| p.y < 0 || p.y + atlas->tile_height > out->size.y)
		return ;
	height = atlas->tile_height;
	tile_data = atlas->img.data
		+ atlas->img.size.x * atlas_pos.y + atlas_pos.x;
	img_data = out->data + out->size.x * p.y + p.x;
	y = 0;
	while (y < height)
	{
		atlas_hline(atlas, img_data, tile_data);
		tile_data += atlas->img.size.x;
		img_data += out->size.x;
		y++;
	}
}
