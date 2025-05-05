/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:52:08 by dath              #+#    #+#             */
/*   Updated: 2025/04/03 17:32:30 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_face	get_character_orientation(char c)
{
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'E')
		return (EAST);
	if (c == 'W')
		return (WEST);
	return (0);
}

float	face_to_angle(t_face c)
{
	const float	table[] = {
	[0] = 0,
	[NORTH] = -PI / 2,
	[SOUTH] = PI / 2,
	[EAST] = 0,
	[WEST] = PI,
	};

	return (table[c]);
}
