/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:41:57 by dath              #+#    #+#             */
/*   Updated: 2025/04/29 19:14:55 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

static inline __attribute__((always_inline))
	t_color	*get_addr(t_img *img, t_point p)
{
	return (img->data + p.y * img->size.x + p.x);
}

void	gfx_put(t_gfx *gfx, t_point p, t_color c)
{
	*get_addr(gfx->screen, p) = c;
}

void	img_put(t_img *img, t_point p, t_color c)
{
	*get_addr(img, p) = c;
}

t_color	img_get(t_img *img, t_point p)
{
	return (*get_addr(img, p));
}

void	gfx_render(t_gfx *gfx)
{
	t_img	*tmp;

	mlx_put_image_to_window(gfx->mlx, gfx->win, gfx->screen->mlx_img, 0, 0);
	tmp = gfx->screen;
	gfx->screen = gfx->back;
	gfx->back = tmp;
}
