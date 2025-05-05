/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:26:12 by lguerbig          #+#    #+#             */
/*   Updated: 2025/03/07 15:19:44 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "gfx.h"
# include "map.h"

typedef enum e_identifiers
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}	t_identifiers;

int		validate_and_parse_map(t_map *map);
int		load_data_from_file(t_gfx *gfx, char *filename);
int		get_textures(t_gfx *gfx, int fd);
int		get_colors(t_gfx *gfx, t_identifiers id, char *colors_line);

#endif
