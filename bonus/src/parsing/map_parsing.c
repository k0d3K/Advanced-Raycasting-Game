/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:48:53 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/16 11:56:34 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>
#include <sys/param.h>

static char	*check_char(t_map *map, t_point p,
	int *player_found, int *exit_found)
{
	char	c;

	c = map->map[p.y][p.x];
	map->tile_data[p.y][p.x].floor_height = get_wall_height(c);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*player_found)
			return (ERR_TOO_MANY_PLAYERS);
		*player_found = 1;
		map->start_pos = p;
		map->start_orientation = get_character_orientation(c);
	}
	else if (c == 'e')
	{
		if (*exit_found)
			return (ERR_TOO_MANY_EXIT);
		*exit_found = 1;
		map->end_pos = p;
		map->map[p.y][p.x] = 'D';
	}
	else if (!ft_isdigit(c) && c != ' ' && c != 'D')
		return (ERR_INVALID_CHAR);
	return (NULL);
}

static char	*
	validate_map_characters(t_map *map, int *x, int *y)
{
	char	*err;
	int		player_found;
	int		exit_found;

	player_found = 0;
	exit_found = 0;
	while (*y < map->height)
	{
		*x = 0;
		while (*x < map->width)
		{
			err = check_char(map, point(*x, *y), &player_found, &exit_found);
			if (err)
				return (err);
			map->highest_wall = MAX(map->highest_wall,
					get_wall_height(map->map[*y][*x]));
			(*x)++;
		}
		(*y)++;
	}
	if (!player_found)
		return (ERR_PLAYER_NOT_FOUND);
	if (!exit_found)
		return (ERR_EXIT_NOT_FOUND);
	return (NULL);
}

static int	ensure_map_is_closed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!check_tile_surroundings(map, x, y))
			{
				if (get_character_orientation(map->map[y][x]))
					print_erroneous_line(map, x, y,
						ERR_MISPLACED_PLAYER);
				else
					print_erroneous_line(map, x, y,
						ERR_INVALID_LAYOUT);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	allocate_tile_data(t_map *map)
{
	int	i;

	map->tile_data = ft_calloc(map->height + 1, sizeof(t_tile *));
	if (!map->tile_data)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->tile_data[i] = ft_calloc(map->width + 1, sizeof(t_tile));
		if (!map->tile_data)
		{
			ft_free_matrix((void **)map->tile_data, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_and_parse_map(t_map *map)
{
	char	*err;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!allocate_tile_data(map))
		return (0);
	err = validate_map_characters(map, &x, &y);
	if (err)
	{
		print_erroneous_line(map, x, y, err);
		return (0);
	}
	replace_height(map, map->start_pos);
	if (!ensure_map_is_closed(map))
		return (0);
	return (1);
}
