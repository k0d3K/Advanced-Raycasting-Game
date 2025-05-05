/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:50:44 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/26 18:13:39 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

int	img_init(t_gfx *gfx, t_img *img, t_point size)
{
	void	*res;
	int		bpp;
	int		size_line;
	int		endian;

	res = mlx_new_image(gfx->mlx, size.x, size.y);
	if (!res)
		return (0);
	img->data = (t_color *)mlx_get_data_addr(res,
			&bpp,
			&size_line,
			&endian);
	img->size = size;
	img->mlx_img = res;
	return (1);
}

void	clear_img(t_img *img, t_color clear_color)
{
	int		x;
	int		y;
	t_color	*data;

	data = img->data;
	y = img->size.y;
	while (--y >= 0)
	{
		x = img->size.x;
		while (--x >= 0)
			*data++ = clear_color;
	}
}
