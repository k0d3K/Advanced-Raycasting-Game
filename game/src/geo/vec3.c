/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:57:08 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 16:39:22 by lguerbig         ###   ########.fr       */
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
