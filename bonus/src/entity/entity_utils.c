/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:40:34 by dath              #+#    #+#             */
/*   Updated: 2025/04/18 19:23:25 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"

void	entity_check_if_pathfinding_should_be_refreshed(t_entity *e)
{
	t_point	new_whole_position;

	new_whole_position = (t_point){{e->plane_pos.x, e->plane_pos.y}};
	e->need_to_refresh_pathfinding = e->need_to_refresh_pathfinding
		|| (new_whole_position.x != e->whole_position.x
			|| new_whole_position.y != e->whole_position.y);
	e->whole_position = new_whole_position;
}
