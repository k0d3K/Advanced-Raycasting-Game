/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:39:11 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/10 19:42:52 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "gfx.h"

typedef struct s_raycast
{
	float		distance;
	float		x_ratio;
	t_cardinal	wall_face;
}	t_raycast;

t_raycast	raycast(t_vec2 ppos, t_vec2 dir, t_gfx *gfx, float max_distance);

#endif
