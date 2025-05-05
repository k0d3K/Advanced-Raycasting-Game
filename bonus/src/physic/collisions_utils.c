/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:53:56 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/05 15:31:07 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include <sys/param.h>

static __always_inline
	float	clamp(float a, float min, float max)
{
	return (MAX(min, MIN(a, max)));
}

static t_vec3	point_on_axis(t_caps b)
{
	if (b.closest.z >= b.top.z)
		return (b.top);
	else if (b.closest.z <= b.bottom.z)
		return (b.bottom);
	b.bottom.z = b.closest.z;
	return (b.bottom);
}

int	aabb_capsule_collision(t_aabb a, t_caps *b)
{
	t_vec3	point;
	float	dist;

	b->bottom = vec3(b->pos.x, b->pos.y, b->pos.z - b->height / 2 + b->radius);
	b->top = vec3(b->pos.x, b->pos.y, b->pos.z + b->height / 2 - b->radius);
	b->closest.x = clamp(b->pos.x, a.pos.x, a.pos.x + a.size.x);
	b->closest.y = clamp(b->pos.y, a.pos.y, a.pos.y + a.size.y);
	b->closest.z = clamp(b->pos.z, a.pos.z, a.pos.z + a.size.z);
	point = point_on_axis(*b);
	point.v = point.v - b->closest.v;
	dist = vec3_length(point);
	if (dist <= b->radius)
	{
		if (dist == 0.0f)
			b->pos.z += b->radius;
		else
			b->pos.v = b->pos.v + vec3_normalize(point).v * (b->radius - dist);
		return (1);
	}
	return (0);
}

static void	find_closests(t_caps *a, t_caps *b)
{
	if (b->top.z <= a->bottom.z)
	{
		b->closest = b->top;
		a->closest = a->bottom;
	}
	else if (a->top.z <= b->bottom.z)
	{
		a->closest = a->top;
		b->closest = b->bottom;
	}
	else if (a->top.z <= b->top.z)
	{
		a->closest = a->top;
		a->closest.z -= (a->top.z - b->bottom.z) / 2;
		b->closest = b->bottom;
		b->closest.z += (a->top.z - b->bottom.z) / 2;
	}
	else
	{
		a->closest = a->bottom;
		a->closest.z += (b->top.z - a->bottom.z) / 2;
		b->closest = b->top;
		b->closest.z -= (b->top.z - a->bottom.z) / 2;
	}
}

/**
 * b is the caaspule that is gonna be mooving in case of collision
 */
int	capsule_capsule_collision(t_caps a, t_caps *b)
{
	t_vec3	diff;
	float	dist;

	a.bottom = vec3(a.pos.x, a.pos.y, a.pos.z - a.height / 2 + b->radius);
	a.top = vec3(a.pos.x, a.pos.y, a.pos.z + a.height / 2 + b->radius);
	b->bottom = vec3(b->pos.x, b->pos.y, b->pos.z - b->height / 2 - b->radius);
	b->top = vec3(b->pos.x, b->pos.y, b->pos.z + b->height / 2 - b->radius);
	find_closests(&a, b);
	diff.v = b->closest.v - a.closest.v;
	dist = vec3_length(diff);
	if (dist <= a.radius + b->radius)
	{
		if (dist == 0.0f)
			b->pos.z += b->radius;
		else
			b->pos.v = b->pos.v
				+ vec3_normalize(diff).v * (a.radius + b->radius - dist);
		return (1);
	}
	return (0);
}
