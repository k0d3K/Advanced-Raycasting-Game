/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:57:22 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/29 19:15:22 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include <sys/param.h>

static int	check_entity_data(t_map map, t_entity *e)
{
	float	floor_height;

	e->height = MIN(e->height, MAX_ENTITY_SIZE);
	e->width = MIN(e->width, MAX_ENTITY_SIZE);
	if (!check_in_bounds((int)e->pos.x, (int)e->pos.y, &map, NULL))
	{
		error(ERR_POS_OOB, e->pos.x, e->pos.y);
		return (0);
	}
	floor_height = map.tile_data[(int)e->pos.y][(int)e->pos.x].floor_height;
	if (floor_height == -1)
	{
		error(ERR_POS_OOB, e->pos.x, e->pos.y);
		return (0);
	}
	if (floor_height == map.highest_wall)
	{
		error(ERR_POS_TOO_HIGHT, e->pos.x, e->pos.y);
		return (0);
	}
	if (e->type == T_COIN)
		e->pos.z = floor_height + COL_DIST;
	else
		e->pos.z = floor_height + e->height / 2;
	return (1);
}

int	parse_entities(t_map map, t_entity_list *entities)
{
	size_t	i;

	i = 0;
	while (i < entities->len)
	{
		if (!check_entity_data(map, &entities->arr[i]))
			return (0);
		i++;
	}
	return (1);
}
