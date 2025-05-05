/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:57:08 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/18 14:38:53 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include <math.h>

t_vec3	vec3(float x, float y, float z)
{
	return ((t_vec3){{x, y, z}});
}

float	vec3_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	mag;

	mag = vec3_length(v);
	return ((t_vec3){{v.x / mag, v.y / mag, v.z / mag}});
}

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	vec3_angle(t_vec3 v1, t_vec3 v2)
{
	float	dot;
	float	length1;
	float	length2;

	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	length1 = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	length2 = sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	return (acosf(dot / (length1 * length2)));
}
