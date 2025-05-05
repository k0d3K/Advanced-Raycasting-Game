/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:53:56 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/05 15:30:41 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "raycast.h"
#include "collision.h"
#include <sys/param.h>

static t_caps	init_capsule(t_vec3 pos, float radius, float height)
{
	t_caps	capsule;

	capsule.pos = pos;
	capsule.radius = radius;
	capsule.height = height;
	return (capsule);
}

static void	secure_up_down(t_entity *entity, t_caps capsule, int highest_wall)
{
	if (entity->pos.z > highest_wall)
	{
		entity->pos.z = highest_wall;
		entity->speed.z = 0;
	}
	if (entity->pos.z < capsule.radius)
	{
		entity->pos.z = capsule.radius;
		entity->speed = vec3(0, 0, 0);
		entity->accel = vec3(0, 0, 0);
		entity->nb_jump = 0;
	}
}

static void	physic_collision(
	t_entity *entity, t_caps capsule, t_vec3 pos, int hit)
{
	t_vec3	diff;

	entity->accel.z = -G;
	diff.v = pos.v - capsule.pos.v;
	if (diff.z < 0 && hit)
	{
		entity->speed = vec3(0, 0, 0);
		entity->accel = vec3(0, 0, 0);
		entity->nb_jump = 0;
	}
	entity->pos = capsule.pos;
}

/**
 * @brief Check if a given position is colliding with a wall.
 * 
 * @param gfx The main structure of the program.
 * @param pos The position to check.
 * @param last The last position of the player.
 * 
 * @return The new position of the player.
 */
int	check_map_collisions(t_gfx *gfx, t_entity *entity, t_vec3 pos)
{
	t_point	check;
	t_caps	capsule;
	int		hit;

	capsule = init_capsule(pos, entity->width / 2, entity->height);
	hit = 0;
	check.y = (int)pos.y - 1;
	while (check.y <= (int)pos.y + 1)
	{
		check.x = (int)pos.x - 1;
		while (check.x <= (int)pos.x + 1)
		{
			if (!check_tile_collision(&gfx->map, &capsule, check, &hit))
			{
				entity->plane_pos = vec2(0.5f + gfx->map.start_pos.x,
						0.5f + gfx->map.start_pos.y);
				return (0);
			}
			check.x++;
		}
		check.y++;
	}
	physic_collision(entity, capsule, pos, hit);
	secure_up_down(entity, capsule, gfx->map.highest_wall);
	return (hit);
}

int	check_entities_collisions(t_gfx *gfx, t_entity *entity, unsigned int i)
{
	t_caps		capsule_a;
	t_caps		capsule_b;
	int			hit;
	t_entity	*e;

	capsule_a = init_capsule(entity->pos, entity->width / 2, entity->height);
	hit = 0;
	i++;
	while (i < gfx->entities.len)
	{
		e = &gfx->entities.arr[i];
		if (!e->is_dead && (e->type == T_ENEMY || entity == &gfx->player))
		{
			capsule_b = init_capsule(e->pos, e->width / 2, e->height);
			if (capsule_capsule_collision(capsule_a, &capsule_b)
				&& entity == &gfx->player)
				collision_effect(gfx, e, &hit);
			e->pos = capsule_b.pos;
		}
		i++;
	}
	return (hit);
}
