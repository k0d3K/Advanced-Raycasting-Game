/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:17:17 by lguerbig          #+#    #+#             */
/*   Updated: 2025/03/08 00:33:07 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>

static char	*
	validate_map_characters(t_map *map, int *x, int *y, int player_found)
{
	char		c;
	t_cardinal	card;

	while (*y < map->height)
	{
		*x = 0;
		while (*x < map->width)
		{
			c = map->map[*y][*x];
			card = get_character_orientation(c);
			if (card)
			{
				if (player_found)
					return (ERR_TOO_MANY_PLAYERS);
				player_found = 1;
				map->start_pos = point(*x, *y);
				map->start_orientation = card;
			}
			else if (c != '0' && c != '1' && c != ' ')
				return (ERR_INVALID_CHAR);
			(*x)++;
		}
		(*y)++;
	}
	return ((char *)(!player_found * (size_t)ERR_PLAYER_NOT_FOUND));
}

static void	print_erroneous_line(t_map *map, int x, int y, char *err)
{
	char	*line;
	int		i;

	error(err);
	i = 0;
	if (y > 0)
		ft_putendl_fd(map->map[y - 1], 2);
	line = map->map[y];
	while (i < x)
		write(2, &line[i++], 1);
	write(2, CONSOLE_RED, sizeof(CONSOLE_RED));
	write(2, &line[i++], 1);
	write(2, CONSOLE_RESET, sizeof(CONSOLE_RESET));
	while (i < map->width)
		write(2, &line[i++], 1);
	write(2, "\n", 1);
	i = -1;
	while (++i < x)
		write(2, " ", 1);
	write(2, UNICODE_ARROW "\n", sizeof(UNICODE_ARROW "\n"));
	if (y + 1 < map->height)
		ft_putendl_fd(map->map[y + 1], 2);
}

static int	check_tile_surroundings(t_map *map, int x, int y)
{
	char	c;

	c = map->map[y][x];
	if (c == '1' || c == ' ')
		return (1);
	if (x - 1 < 0 || (map->map[y][x - 1] == ' '
		&& !get_character_orientation(map->map[y][x - 1])))
		return (0);
	if (x + 1 >= map->width || (map->map[y][x + 1] == ' '
		&& !get_character_orientation(map->map[y][x + 1])))
		return (0);
	if (y - 1 < 0 || (map->map[y - 1][x] == ' '
		&& !get_character_orientation(map->map[y - 1][x])))
		return (0);
	if (y + 1 >= map->height || (map->map[y + 1][x] == ' '
		&& !get_character_orientation(map->map[y + 1][x])))
		return (0);
	return (1);
}

static int	ensure_map_is_closed(t_map *map)
{
	int		x;
	int		y;

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

int	validate_and_parse_map(t_map *map)
{
	char	*err;
	int		x;
	int		y;

	x = 0;
	y = 0;
	err = validate_map_characters(map, &x, &y, 0);
	if (err)
	{
		print_erroneous_line(map, x, y, err);
		return (0);
	}
	return (ensure_map_is_closed(map));
}
