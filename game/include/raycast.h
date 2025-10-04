/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:39:11 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:40:51 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "geo.h"
# include "map.h"
# include <math.h>

typedef struct s_raycast
{
	float		distance;
	float		x_ratio;
	t_face		wall_face;
	float		wall_height;
	t_point		pos;
	int			n_faces_visible;
	t_vec2		dir;
	float		inv_fish_eye_corr;
	float		dist_from_ground;
}	t_raycast;

static const t_raycast			g_empty_raycast = {
	NAN, NAN, 0, 0, {{0, 0}}, 0, {{NAN, NAN}}, NAN, 0
};

typedef struct s_gfx			t_gfx;

typedef struct s_raycast_vars
{
	char			first;
	char			c;
	t_vec2			ppos;
	t_vec2			pos;
	t_raycast		res;
	float			max_distance;
	t_gfx			*gfx;

	int				cur_max_len;
	t_raycast		front;
	int				need_to_add_back;
	int				previous_wall_height;
	t_tile			tile;
}	t_raycast_vars;

void		safe_put(t_gfx *gfx, t_vec2 pos);
t_face		first_border_hit(t_vec2 pos, t_vec2 dir, t_vec2 border);
float		raycast_calc_max_dist(
				t_vec2 ppos, t_vec2 dir, t_gfx *gfx, float prev_max_dist);
int			raycast_init(
				t_raycast_vars *v, t_vec2 dir, t_gfx *gfx, float max_distance);
void		fisrt_tile(t_raycast_vars *v, t_vec2 dir);
void		get_door_height(t_raycast_vars *v, t_vec2 dir);
t_raycast	raycast_get_pos_on_texture(t_raycast_vars v, t_vec2 dir);
t_raycast	raycast(t_gfx *gfx, t_vec3 pos, t_vec2 dir, float max_distance);
t_raycast	door_raycast(t_gfx *gfx, t_raycast res, t_vec2 pos, t_vec2 dir);
int			next_coord(t_raycast_vars *v, t_vec2 dir);
t_vec2		door_find_borders(t_vec2 pos, t_vec2 dir, t_tile tile);

typedef struct s_render_thread	t_render_thread;

typedef struct s_raycast_pair
{
	t_raycast	front;
	t_raycast	back;
}	t_raycast_pair;

void		raycast_add_back(t_raycast_vars *v, t_vec2 dir,
				t_raycast_pair *rcs, int *rcs_len);
void		raycast_add_front(t_raycast_vars *v, t_vec2 dir);
void		continuous_raycast(t_render_thread *rd, t_vec2 dir);

#endif
