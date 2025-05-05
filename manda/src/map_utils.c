/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:32:51 by lguerbig          #+#    #+#             */
/*   Updated: 2025/03/06 19:50:36 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/**
 * @brief Check if a given position is in bounds of the map
 * 
 * @param x x-coordinate
 * @param y y-coordinate
 * @param map map to check in
 * 
 * @return 1 if in bounds, 0 otherwise
 */
int	check_in_bounds(int x, int y, t_map *map)
{
	return (x >= 0 && x < map->width && y >= 0 && y < map->height);
}

/**
 * @brief Check if the given coordinates are in the map.
 * 
 * @param pos The position to check.
 * @param dir The direction of the ray.
 * @param border_type The type of the border hit.
 * @param map The map.
 * 
 * @return The value in the map if the coordinates are in it , space otherwise.
 */
char	get_value_here(t_vec2 pos, t_vec2 dir,
	t_cardinal border_type, t_map *map)
{
	t_point	tile_to_check;
	t_point	pos_integer;

	if (pos.x < 0 || pos.y < 0)
		return (' ');
	pos_integer.x = pos.x;
	pos_integer.y = pos.y;
	if (border_type == NORTH || border_type == SOUTH)
	{
		tile_to_check.x = pos_integer.x;
		tile_to_check.y = pos_integer.y - (dir.y < 0);
		if (check_in_bounds(tile_to_check.x, tile_to_check.y, map))
			return (map->map[tile_to_check.y][tile_to_check.x]);
	}
	else
	{
		tile_to_check.x = pos_integer.x - (dir.x < 0);
		tile_to_check.y = pos_integer.y;
		if (check_in_bounds(tile_to_check.x, tile_to_check.y, map))
			return (map->map[tile_to_check.y][tile_to_check.x]);
	}
	return (' ');
}
