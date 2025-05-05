/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:32:51 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/05 15:26:18 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <limits.h>

/**
 * @brief Check if a given position is in bounds of the map
 * 
 * @param x x-coordinate
 * @param y y-coordinate
 * @param map map to check in
 * 
 * @return 1 if in bounds, 0 otherwise
 */
int	check_in_bounds(int x, int y, t_map *map, char *ret)
{
	int	res;

	res = (x >= 0 && x < map->width && y >= 0 && y < map->height);
	if (res && ret)
		*ret = map->map[y][x];
	return (res);
}

/**
 * @brief Check if the given coordinates are in the map.
 * 
 * @param pos The position to check.
 * @param dir The direction of the ray.
 * @param map The map.
 * 
 * @return The value in the map if the coordinates are in it , space otherwise.
 */
char	get_value_here(t_vec2 pos, t_vec2 dir, t_map *map)
{
	t_point	tile_to_check;
	char	c;

	tile_to_check = get_position(pos, dir);
	if (check_in_bounds(tile_to_check.x, tile_to_check.y, map, &c))
		return (c);
	return (' ');
}

t_point	get_position(t_vec2 pos, t_vec2 dir)
{
	t_point	p;

	if ((int)pos.x == pos.x)
		p.x = (int)pos.x - (dir.x < 0);
	else
		p.x = (int)pos.x;
	if ((int)pos.y == pos.y)
		p.y = (int)pos.y - (dir.y < 0);
	else
		p.y = (int)pos.y;
	p.x -= (pos.x < 0);
	p.y -= (pos.y < 0);
	return (p);
}
