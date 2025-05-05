/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:21:06 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 16:42:07 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# include "geo.h"

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

#endif
