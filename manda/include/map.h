/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:42:56 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/07 15:11:32 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdint.h>
# include "geo.h"

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
	t_point		start_pos;
	t_cardinal	start_orientation;
}	t_map;

int		check_in_bounds(int x, int y, t_map *map);
char	get_value_here(t_vec2 pos, t_vec2 dir,
			t_cardinal border_type, t_map *map);

#endif
