/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:29:17 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/29 19:34:52 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "gfx.h"
#include "libft.h"
#include "utils.h"
#include "bitmap.h"
#include <assert.h>
#include <stdarg.h>

static char	*load_textures_batch(t_gfx *gfx, char **err)
{
	const char	*identifiers[N_TEXTURES] = {"NO", "SO", "WE", "EA", "DO",
		"F", "C", "e"};
	int			i;
	t_img		*ptr;
	char		*cur;

	i = 0;
	ptr = (t_img *)&gfx->textures;
	while (i < N_TEXTURES)
	{
		cur = dict_fetch(&gfx->texture_files, (char *)identifiers[i]);
		*err = bitmap_load(gfx, &ptr[i], cur);
		if (*err)
			return (cur);
		dict_remove(&gfx->texture_files, (char *)identifiers[i]);
		i++;
	}
	*err = NULL;
	return (NULL);
}

static char	*load_sprites_batch(t_gfx *gfx, char **err)
{
	size_t		i;
	t_atlas		*ptr;
	char		*cur;
	uint16_t	x;
	uint16_t	y;

	gfx->textures.sprites = ft_calloc(gfx->texture_files.main_list.len,
			sizeof(t_atlas));
	if (!gfx->textures.sprites)
		return (ERR_MALLOC);
	ptr = gfx->textures.sprites;
	i = 0;
	while (i < gfx->texture_files.main_list.len)
	{
		cur = gfx->texture_files.main_list.arr[i];
		x = gfx->textures.size_sprites.arr[i] >> 16;
		y = gfx->textures.size_sprites.arr[i] & 0xFFFF;
		*err = atlas_init(gfx, &ptr[i], cur, point(x, y));
		if (*err)
			return (cur);
		i++;
	}
	return (NULL);
}

#define FONT_FILE	"textures/font.bmp"

int	load_static_textures(t_gfx *gfx)
{
	const char	*failed;
	t_point		p;

	if (!gfx_text_init(gfx, FONT_FILE))
		return (0);
	failed = bitmap_load(gfx, &gfx->textures.heart, "textures/heart.bmp");
	if (failed)
	{
		error(ERR_FAILED_TO_LOAD, "textures/heart.bmp", failed);
		return (0);
	}
	failed = bitmap_load(gfx, &gfx->textures.bullet, "textures/bullet.bmp");
	if (failed)
	{
		error(ERR_FAILED_TO_LOAD, "textures/bullet.bmp", failed);
		return (0);
	}
	p = point(6, 1);
	failed = atlas_init(gfx, &gfx->textures.gun, "textures/gun.bmp", p);
	if (failed)
	{
		error(ERR_FAILED_TO_LOAD, "textures/gun.bmp", failed);
		return (0);
	}
	return (1);
}

void	unload_static_textures(t_gfx *gfx)
{
	if (gfx->textures.font.img.mlx_img)
		mlx_destroy_image(gfx->mlx, gfx->textures.font.img.mlx_img);
	if (gfx->textures.heart.mlx_img)
		mlx_destroy_image(gfx->mlx, gfx->textures.heart.mlx_img);
	if (gfx->textures.bullet.mlx_img)
		mlx_destroy_image(gfx->mlx, gfx->textures.bullet.mlx_img);
	if (gfx->textures.gun.img.mlx_img)
		mlx_destroy_image(gfx->mlx, gfx->textures.gun.img.mlx_img);
	if (gfx->game_vars.adventure.start_screen.mlx_img)
		mlx_destroy_image(gfx->mlx,
			gfx->game_vars.adventure.start_screen.mlx_img);
	if (gfx->game_vars.adventure.end_screen.mlx_img)
		mlx_destroy_image(gfx->mlx,
			gfx->game_vars.adventure.end_screen.mlx_img);
	if (gfx->game_vars.adventure.level_end_screen.mlx_img)
		mlx_destroy_image(gfx->mlx,
			gfx->game_vars.adventure.level_end_screen.mlx_img);
	if (gfx->game_vars.adventure.death_screen.mlx_img)
		mlx_destroy_image(gfx->mlx,
			gfx->game_vars.adventure.death_screen.mlx_img);
}

int	load_textures(t_gfx *gfx)
{
	const char	*failed;
	char		*err;

	failed = load_textures_batch(gfx, &err);
	if (failed)
	{
		error(ERR_FAILED_TO_LOAD, failed, err);
		return (0);
	}
	failed = load_sprites_batch(gfx, &err);
	if (failed)
	{
		if (!ft_strcmp((char *)failed, ERR_MALLOC))
			error(ERR_MALLOC);
		else
			error(ERR_FAILED_TO_LOAD, failed, err);
		return (0);
	}
	return (1);
}
