/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:57 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 17:17:00 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include "mlx.h"
# include "geo.h"
# include "img.h"
# include "texture.h"
# include "input.h"
# include "map.h"
# include "rendering.h"
# include "entity.h"
# include "libft.h"
# include "utils.h"
# include "pathfinding.h"
# include "parsing.h"
# include <pthread.h>

typedef enum e_game_state
{
	PLAYING,
	IN_TITLE_SCREEN,
	IN_LEVEL_END_SCREEN,
	IN_DEATH_SCREEN
}	t_game_state;

typedef struct s_game_vars
{
	t_game_state	game_state;
	int				single_level;

	t_adventure		adventure;
	int				player_died;
	int				level_cursor;
	int				level_index;
	float			time_taken_in_level;
	int				n_enemies;
	int				n_coins;
	int				n_enemies_killed;
	int				n_coins_collected;
	int				refresh_stats;
}	t_game_vars;

typedef struct s_gun
{
	int			n_gun_img;
	int			reloading;
	uint64_t	last_shot;
	int			nb_shot_left;
}	t_gun;

typedef struct s_gfx
{
	void					*mlx;
	void					*win;
	t_img					screen1;
	t_img					screen2;
	t_img					*screen;
	t_img					*back;
	t_img					minimap_img;
	t_img					stats_img;
	t_img					hurt_img;
	t_textures				textures;

	float					dt;
	double					time_elapsed;
	float					fov;
	float					tan_half_fov;
	float					max_raycast_distance;
	float					screen_dist;
	float					cam_dir;
	float					sin_cam_dir;

	t_entity				player;
	t_gun					gun;
	t_input					input;

	t_entity_list			entities;
	t_entity				*entity_drawn;
	t_entity				*entity_hit;

	t_map					map;
	t_dict					texture_files;

	t_pathfinding_resources	pf_res;
	t_game_vars				game_vars;

	pthread_cond_t			render_cond;
	pthread_mutex_t			thread_state_lock;
	t_thread_state			thread_state;
	t_render_thread			*render_threads;
}	t_gfx;

int			gfx_init(t_gfx *gfx);
void		gfx_deinit(t_gfx *gfx);
void		gfx_put(t_gfx *gfx, t_point p, t_color c);
void		gfx_render(t_gfx *gfx);
int			gfx_text_init(t_gfx *gfx, char *font_path);
void		gfx_text(t_gfx *gfx, t_point p, char *str);

typedef struct s_bresenham
{
	t_point	from;
	t_point	to;
	t_point	dir;
	t_point	sign;
	int		err;
	int		e2;
}	t_bresenham;

void		gfx_line(t_gfx *gfx, t_point from, t_point to, t_color c);
void		loop(t_gfx *gfx);

t_entity	*entity_add(t_gfx *gfx, t_entity e);
void		sort_entities_by_dist(t_gfx *gfx, t_vec2 pos);
void		gfx_unload_scene(t_gfx *gfx);

void		toggle_level_end_screen(t_gfx *gfx, int died);
void		load_next_level(t_gfx *gfx, int is_first_level);

#endif
