/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:27:04 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/19 14:15:52 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "geo.h"
# include "texture.h"
# include <stddef.h>

typedef enum e_sprite_type
{
	T_ENEMY = 1,
	T_COIN
}	t_sprite_type;

typedef struct s_entity
{
	t_sprite_type	type;
	union
	{
		t_vec3		pos;
		t_vec2		plane_pos;
	};
	t_vec2			player_dist;
	float			dist_to_player;

	t_vec2			dir;
	float			angle;
	float			height;
	float			width;
	t_vec3			accel;
	t_vec3			speed;

	int				nb_jump;
	t_atlas			*atlas;
	int				idx_anim;

	t_point			whole_position;
	int				need_to_refresh_pathfinding;
	int				can_reach_player;
	t_vec2			target_position;

	int				life_point;
	float			hit;
	int				is_dead;
}	t_entity;

typedef struct s_entity_list
{
	t_entity		*arr;
	size_t			cap;
	size_t			len;
}	t_entity_list;

# define LIST_INCREMENT	50

//	player_management.c
void	manage_player(t_gfx *gfx);

//	entity.c
int		entity_list_init(t_entity_list *lst, size_t init_cap);
int		entity_list_add(t_entity_list *lst, t_entity e);
void	entity_list_remove(t_entity_list *lst, size_t start, size_t n);

//	entity_utils.c
void	entity_check_if_pathfinding_should_be_refreshed(t_entity *e);

#endif
