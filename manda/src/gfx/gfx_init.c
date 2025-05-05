/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:36:53 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/12 13:45:11 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "config.h"
#include "libft.h"
#include "utils.h"
#include <X.h>

int	init_screens(t_gfx *gfx)
{
	if (!img_init(gfx, &gfx->screen1, point(WIN_X, WIN_Y)))
		return (0);
	if (!img_init(gfx, &gfx->screen2, point(WIN_X, WIN_Y)))
		return (0);
	gfx->screen = &gfx->screen1;
	gfx->back = &gfx->screen2;
	return (1);
}

int	gfx_init(t_gfx *gfx)
{
	gfx->mlx = mlx_init();
	if (!gfx->mlx)
	{
		error(MLX_INIT_FAIL);
		return (0);
	}
	if (!load_textures(gfx))
		return (0);
	if (!init_screens(gfx))
	{
		error(MLX_IMG_FAIL);
		return (0);
	}
	gfx->win = mlx_new_window(gfx->mlx, WIN_X, WIN_Y, WIN_TITLE, 1);
	if (!gfx->win)
	{
		error(MLX_WIN_FAIL);
		return (0);
	}
	return (1);
}

void	gfx_deinit(t_gfx *gfx)
{
	unload_textures(gfx);
	if (gfx->screen1.mlx_img)
		mlx_destroy_image(gfx->mlx, gfx->screen1.mlx_img);
	if (gfx->screen2.mlx_img)
		mlx_destroy_image(gfx->mlx, gfx->screen2.mlx_img);
	if (gfx->win)
		mlx_destroy_window(gfx->mlx, gfx->win);
	if (gfx->mlx)
		mlx_destroy_display(gfx->mlx);
	if (gfx->map.map)
		ft_clean_matrix((void **)gfx->map.map);
	free(gfx->mlx);
	ft_bzero(gfx, sizeof(t_gfx));
}
