/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:19:20 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:41:22 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

# include "geo.h"
# include "gfx.h"

typedef struct s_aabb
{
	t_vec3	pos;
	t_vec3	size;
}	t_aabb;

typedef struct s_caps
{
	t_vec3	pos;
	float	radius;
	float	height;
	t_vec3	top;
	t_vec3	bottom;
	t_vec3	closest;
}	t_caps;

//	physic
int		check_map_collisions(t_gfx *gfx, t_entity *entity, t_vec3 pos);
int		check_entities_collisions(t_gfx *gfx, t_entity *entity, unsigned int i);

//	collitions
int		check_tile_collision(
			t_map *map, t_caps *capsule, t_point check, int *hit);
void	collision_effect(t_gfx *gfx, t_entity *e, int *hit);

//	colisions_utils
int		aabb_capsule_collision(t_aabb a, t_caps *b);
int		capsule_capsule_collision(t_caps a, t_caps *b);

#endif