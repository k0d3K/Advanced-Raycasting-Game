/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:19:57 by dath              #+#    #+#             */
/*   Updated: 2025/03/25 10:30:20 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include <stdio.h>
#include <math.h>
#include <sys/param.h>

static inline __attribute__((always_inline))
	float	vec2_cross(t_vec2 a, t_vec2 b)
{
	return (a.x * b.y - a.y * b.x);
}

t_vec2	geo_intersection(t_vec2 p1, t_vec2 p2, t_vec2 p3, t_vec2 p4)
{
	t_vec2	r;
	t_vec2	s;
	float	rxs;
	t_vec2	t_u;
	t_vec2	q_p;

	r = (t_vec2)(p2.v - p1.v);
	s = (t_vec2)(p4.v - p3.v);
	rxs = vec2_cross(r, s);
	if (rxs == 0)
		return ((t_vec2){{NAN, NAN}});
	q_p = (t_vec2)(p3.v - p1.v);
	t_u.x = vec2_cross(q_p, s) / rxs;
	t_u.y = vec2_cross(q_p, r) / rxs;
	if (t_u.x >= 0 && t_u.x <= 1 && t_u.y >= 0 && t_u.y <= 1)
		return ((t_vec2){{
				p1.x + t_u.x * r.x,
				p1.y + t_u.x * r.y
			}});
	return ((t_vec2){{NAN, NAN}});
}
