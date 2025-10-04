/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_surroundings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:29:36 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/09 17:29:38 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>
#include <sys/param.h>

static int	get_door_wall_height(t_map *map, t_point p, t_point dir)
{
	t_point	new_p;
	char	c;
	int		height;

	new_p.p = p.p + dir.p;
	c = map->map[new_p.y][new_p.x];
	if (c == 'D')
		height = get_door_wall_height(map, new_p, dir);
	else
		height = get_wall_height(c);
	return (height);
}

static void	horizontal_door_check(t_map *map, t_point p)
{
	int	height_1;
	int	height_2;

	height_1 = get_door_wall_height(map, p, point(-1, 0));
	height_2 = get_door_wall_height(map, p, point(1, 0));
	if (height_1 && height_2)
	{
		map->tile_data[p.y][p.x].door.orientation = 0;
		map->tile_data[p.y][p.x].door.height = MIN(height_1, height_2);
	}
	map->tile_data[p.y][p.x].floor_height = MIN(height_1, height_2);
}

static int	vertical_door_check(t_map *map, t_point p)
{
	int	height_1;
	int	height_2;

	height_1 = get_door_wall_height(map, p, point(0, -1));
	height_2 = get_door_wall_height(map, p, point(0, 1));
	if (height_1 && height_2)
	{
		if (MIN(height_1, height_2) == map->tile_data[p.y][p.x].door.height)
			return (0);
		else if (MIN(height_1, height_2) > map->tile_data[p.y][p.x].door.height)
		{
			map->tile_data[p.y][p.x].door.orientation = 1;
			map->tile_data[p.y][p.x].door.height = MIN(height_1, height_2);
		}
		else
			map->tile_data[p.y][p.x].floor_height = MIN(height_1, height_2);
	}
	else
		map->tile_data[p.y][p.x].floor_height = MIN(height_1, height_2);
	return (1);
}

static int	check_bound_surroundings(t_map *map, int x, int y)
{
	if (x - 1 > 0 && map->map[y][x - 1] != ' '
		&& get_wall_height(map->map[y][x - 1]) != map->highest_wall)
		return (0);
	if (x + 1 < map->width && map->map[y][x + 1] != ' '
		&& get_wall_height(map->map[y][x + 1]) != map->highest_wall)
		return (0);
	if (y - 1 > 0 && map->map[y - 1][x] != ' '
		&& get_wall_height(map->map[y - 1][x]) != map->highest_wall)
		return (0);
	if (y + 1 < map->height && map->map[y + 1][x] != ' '
		&& get_wall_height(map->map[y + 1][x]) != map->highest_wall)
		return (0);
	return (1);
}

int	check_tile_surroundings(t_map *map, int x, int y)
{
	char	c;

	c = map->map[y][x];
	map->tile_data[y][x].pos = (t_point){{x, y}};
	map->tile_data[y][x].floor_height = get_wall_height(c);
	map->tile_data[y][x].type = T_BOX;
	if (c == ' ')
	{
		if (!check_bound_surroundings(map, x, y))
			return (0);
	}
	else if (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1)
	{
		if (get_wall_height(c) != map->highest_wall)
			return (0);
	}
	else if (c == 'D')
	{
		map->tile_data[y][x].type = T_DOOR;
		horizontal_door_check(map, point(x, y));
		if (!vertical_door_check(map, point(x, y)))
			return (0);
		return (map->tile_data[y][x].door.height != 0);
	}
	return (1);
}
