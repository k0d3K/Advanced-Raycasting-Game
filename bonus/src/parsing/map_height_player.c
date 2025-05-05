/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_height_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:48:53 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/16 12:02:44 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>
#include <sys/param.h>

static int	min_positive(int a, int b)
{
	int	min;

	if (a < 0 || b < 0)
		min = (a > 0) * a + (b > 0) * b;
	else
		min = MIN(a, b);
	return (min);
}

void	replace_height(t_map *map, t_point pos)
{
	int	height_1;
	int	height_2;
	int	min;
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	height_1 = 0;
	height_2 = 0;
	if (x - 1 >= 0)
		height_1 = map->tile_data[y][x - 1].floor_height;
	if (x + 1 < map->width)
		height_2 = map->tile_data[y][x + 1].floor_height;
	min = min_positive(height_1, height_2);
	if (y - 1 >= 0)
		height_1 = map->tile_data[y - 1][x].floor_height;
	if (y + 1 < map->height)
		height_2 = map->tile_data[y + 1][x].floor_height;
	min = min_positive(min, height_1);
	min = min_positive(min, height_2);
	map->map[y][x] = min + '0';
	map->tile_data[y][x].floor_height = min;
}
