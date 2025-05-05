/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:42:56 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/16 10:31:39 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdint.h>
# include "geo.h"

typedef enum e_door_state
{
	CLOSING,
	CLOSED,
	OPENING,
	OPENED
}	t_door_state;

typedef struct s_door
{
	t_door_state	state;
	float			status;
	int				orientation;
	int				height;
}	t_door;

typedef enum e_tile_type
{
	T_BOX,
	T_DOOR
}	t_tile_type;

typedef struct s_tile
{
	t_point		pos;
	t_tile_type	type;
	t_door		door;
	int			floor_height;
}	t_tile;

typedef struct s_map
{
	int			width;
	int			height;
	int			highest_wall;
	char		**map;
	t_tile		**tile_data;
	t_point		start_pos;
	t_point		end_pos;
	t_face		start_orientation;
}	t_map;

int		check_in_bounds(int x, int y, t_map *map, char *ret);
char	get_value_here(t_vec2 pos, t_vec2 dir, t_map *map);
t_point	get_position(t_vec2 pos, t_vec2 dir);

#endif
