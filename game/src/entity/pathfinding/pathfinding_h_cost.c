/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_h_cost.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:42:37 by dath              #+#    #+#             */
/*   Updated: 2025/04/14 17:43:43 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"

uint32_t	pf_calculate_h_cost(t_pathfinding_vars *v, t_point p)
{
	int32_t	diff_x;
	int32_t	diff_y;

	diff_x = v->end_pos.x - p.x;
	diff_y = v->end_pos.y - p.y;
	diff_x = abs(diff_x);
	diff_y = abs(diff_y);
	return ((diff_x + diff_y) * H_V_MOVEMENT_COST);
}
