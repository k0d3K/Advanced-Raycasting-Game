/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:02:39 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/18 14:38:40 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include <math.h>

t_vec2	vec2(float x, float y)
{
	return ((t_vec2){{x, y}});
}

float	vec2_length(t_vec2 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

t_vec2	vec2_normalize(t_vec2 v)
{
	float	mag;

	mag = sqrtf(v.x * v.x + v.y * v.y);
	return ((t_vec2){{v.x / mag, v.y / mag}});
}

float	vec2_dot(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float	vec2_angle(t_vec2 v1, t_vec2 v2)
{
	float	dot;
	float	det;

	dot = v1.x * v2.x + v1.y * v2.y;
	det = v1.x * v2.y - v1.y * v2.x;
	return (atan2f(dot, det));
}
