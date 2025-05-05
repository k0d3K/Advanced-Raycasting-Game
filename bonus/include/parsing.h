/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:26:12 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/28 15:29:29 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "map.h"
# include "utils.h"
# include "entity.h"

typedef enum e_identifiers
{
	NO,
	SO,
	WE,
	EA,
	DO,
	F,
	C
}	t_identifiers;

typedef struct s_gfx	t_gfx;

int		validate_and_parse_map(t_map *map);
int		load_data_from_file(t_gfx *gfx, char *filename);
int		get_textures(t_gfx *gfx, int fd);
int		get_sprites(t_gfx *gfx, int fd);

//	read_utils
char	*skip_empty_lines(int fd);
char	*get_line(int fd);
char	**get_texture_line_infos(char *line);
char	**get_sprite_line_infos(char *line);

void	set_player_variables(t_gfx *gfx);
int		init_resources(t_gfx *gfx);

//	entities_parsing
int		parse_entities(t_map map, t_entity_list *entities);

//	check_suroundings
int		check_tile_surroundings(t_map *map, int x, int y);

//	map_height_player
void	replace_height(t_map *map, t_point pos);

//	parsing_utils
float	my_atof(const char *str);
void	print_erroneous_line(t_map *map, int x, int y, char *err);

typedef struct s_adventure
{
	t_dict		properties;
	t_str_list	map_lst;
	t_img		start_screen;
	t_img		end_screen;
	t_img		level_end_screen;
	t_img		death_screen;
}	t_adventure;

typedef struct s_adventure_parse_vars
{
	t_adventure	*res;
	int			fd;
	char		*line;
	char		*trimmed;
	int			in_map_list;
	int			parsed_map_list;
}	t_adventure_parse_vars;

int		av_parse_prop(t_adventure_parse_vars *v, char *line, char *sep);
int		av_parse_map_entry(t_adventure_parse_vars *v, char *line);
int		adventure_parse(t_gfx *gfx, char *file, t_adventure *adventure);
int		av_handle_brackets(t_adventure_parse_vars *v, char *line);
int		av_raise_error(t_adventure_parse_vars *v, char *fmt, ...);

#endif
