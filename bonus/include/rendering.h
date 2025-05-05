/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:58:32 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:41:11 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "raycast.h"
# include "img.h"
# include <pthread.h>

typedef struct s_gfx	t_gfx;

typedef struct s_render_thread
{
	t_gfx			*gfx;
	int				id;
	pthread_t		thread;
	pthread_mutex_t	lock;
	int				thread_initialized;
	int				frame_rendered;
	t_raycast_pair	*rcs;
	int				rcs_len;
}	t_render_thread;

typedef enum s_thread_state
{
	STATE_INITIALIZING,
	STATE_ABORT,
	STATE_RUNNING,
	STATE_STOP
}	t_thread_state;

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
	int			n_faces_to_draw;
	t_point		screen;
	t_color		*mid_screen;
}	t_vline_data;

void	*render_thread(t_render_thread *self);

void	render(t_render_thread *rd, int from, int to);

void	calculate_floor_ceil_ratios(
			t_gfx *gfx, t_raycast rc, t_vline_data *data);
void	calculate_floor_ceil_heights(
			t_gfx *gfx, t_vline_data *data, int screen_x);
void	draw_line(t_color *line, t_color *stop, t_color c);
void	draw_cube(
			t_img *img,
			t_vline_data vline,
			t_color *data_line,
			t_color *data_end);
void	draw_sprite(
			t_atlas *atlas,
			t_vline_data vline,
			t_color *data_line,
			t_color *data_end);

typedef struct s_draw_top_vars
{
	float	true_height;
	int		total_steps;
	t_color	*beg_line;
	t_color	*stop_line;
	t_color	*mid_screen;
	float	x_ratio;
	float	x_ratio_step;
}	t_draw_top_vars;

void	draw_top(t_gfx *gfx,
			t_raycast_pair rc_pair,
			t_img *img,
			int screen_x);

typedef struct s_drawing
{
	t_point	pos;
	t_point	size;
	int		thick;
	int		radius;
}	t_drawing;

void	render_skybox(t_gfx *gfx, int from, int to, t_img tex);
void	render_hurt_effect(t_gfx *gfx, int from, int to);
void	clear_img(t_img *img, t_color clear_color);
void	draw_bullets(t_gfx *gfx, t_drawing d);
void	draw_heart(t_gfx *gfx, t_drawing d);
void	render_life_bar(t_gfx *gfx);

#endif
