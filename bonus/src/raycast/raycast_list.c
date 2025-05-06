/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:12:04 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 17:00:23 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <sys/param.h>

static t_face	swap_face(t_face c)
{
	if (c == NORTH)
		return (SOUTH);
	if (c == SOUTH)
		return (NORTH);
	if (c == EAST)
		return (WEST);
	return (EAST);
}

void	raycast_add_back(
	t_raycast_vars *v,
	t_vec2 dir,
	t_raycast_pair *rcs,
	int *rcs_len)
{
	t_raycast	res;

	res = raycast_get_pos_on_texture(*v, dir);
	res.x_ratio = 1.0f - res.x_ratio;
	res.wall_face = swap_face(res.wall_face);
	if (*rcs_len != 0)
		v->cur_max_len = MAX(v->cur_max_len, v->res.wall_height);
	rcs[(*rcs_len)++] = (t_raycast_pair){v->front, res};
	v->need_to_add_back = 0;
	v->previous_wall_height = res.wall_height;
}

void	raycast_add_front(t_raycast_vars *v, t_vec2 dir)
{
	v->front = raycast_get_pos_on_texture(*v, dir);
	v->need_to_add_back = 1;
	v->front.n_faces_visible = v->front.wall_height - v->previous_wall_height;
}
