/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:02:39 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 16:40:25 by lguerbig         ###   ########.fr       */
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
