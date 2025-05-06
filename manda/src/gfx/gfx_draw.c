/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:41:57 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 16:01:13 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "config.h"
#include "mlx.h"

static inline __attribute__((always_inline))
	t_color	*get_addr(t_img *img, t_point p)
{
	int		offset;
	t_color	*addr;

	offset = p.y * img->size.x + p.x;
	addr = img->data + offset;
	return (addr);
}

void	img_put(t_img *img, t_point p, t_color c)
{
	*get_addr(img, p) = c;
}

void	gfx_render(t_gfx *gfx)
{
	t_img	*tmp;

	mlx_put_image_to_window(gfx->mlx, gfx->win, gfx->screen->mlx_img, 0, 0);
	tmp = gfx->screen;
	gfx->screen = gfx->back;
	gfx->back = tmp;
}
