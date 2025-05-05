/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:58:32 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/07 15:19:17 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "gfx.h"
# include "raycast.h"

typedef struct s_vline_data
{
	t_raycast	rc;
	float		floor_ratio;
	float		ceil_ratio;
	float		raw_floor_height;
	float		raw_ceil_height;
	int			floor_height;
	int			ceil_height;
	int			unclamped_ceil_height;
	int			unclamped_floor_height;
}	t_vline_data;

void	render(t_gfx *gfx);
void	calculate_floor_ceil_ratios(
			t_gfx *gfx, t_raycast rc, t_vline_data *data);
void	calculate_floor_ceil_heights(t_vline_data *data);
void	draw_line(t_color *line, t_color *stop, t_color c);

#endif
