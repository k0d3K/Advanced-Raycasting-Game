/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:56:39 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/16 19:28:48 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include <fcntl.h>
#include "utils.h"
#include "parsing.h"

/**
 * @brief Read the map from the file
 * 
 * @param fd The file descriptor of the opened file
 * 
 * @return char** The map
 */
static char	**read_tab(int fd)
{
	t_str_list	lst;
	char		*line;

	lst.arr = NULL;
	line = skip_empty_lines(fd);
	if (!line)
		error(ERR_NO_MAP);
	else
		str_list_init(&lst, 50, 1);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		str_list_add(&lst, line);
		if (!lst.arr)
		{
			error(ERR_MALLOC);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (lst.arr);
}

static int	resize(char **map, size_t width, size_t height)
{
	size_t	i;
	size_t	size_line;
	char	*new_str;

	i = 0;
	while (i < height)
	{
		size_line = ft_strlen(map[i]);
		if (size_line != width)
		{
			new_str = (char *)malloc(sizeof(char) * (width + 1));
			if (!new_str)
				return (0);
			ft_memcpy(new_str, map[i], size_line);
			ft_memset(new_str + size_line, ' ', width - size_line);
			new_str[width] = '\0';
			free(map[i]);
			map[i] = new_str;
		}
		++i;
	}
	return (1);
}

static int	get_map(t_gfx *gfx, int fd)
{
	int		i;
	int		witdh;
	char	**map;

	map = read_tab(fd);
	if (!map)
		return (0);
	witdh = 0;
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > witdh)
			witdh = ft_strlen(map[i]);
		i++;
	}
	gfx->map.width = witdh;
	gfx->map.height = size_tab(map);
	gfx->map.map = map;
	if (!resize(map, gfx->map.width, gfx->map.height))
	{
		error(ERR_MALLOC);
		return (0);
	}
	return (1);
}

int	init_data_loading(t_gfx *gfx, char *filename)
{
	int	fd;

	if (!dict_init(&gfx->texture_files, 1))
	{
		error(ERR_MALLOC);
		return (0);
	}
	if (!entity_list_init(&gfx->entities, 50))
	{
		error(ERR_MALLOC);
		return (0);
	}
	if (!uint_list_init(&gfx->textures.size_sprites, 50))
	{
		error(ERR_MALLOC);
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error(ERR_OPEN, filename);
		return (0);
	}
	return (fd);
}

/**
 * @brief Load the data from the file 
 * 
 * @param gfx The main structure
 * @param filename The name of the file
 */
int	load_data_from_file(t_gfx *gfx, char *filename)
{
	int	fd;
	int	result;

	if (gfx->map.map)
		gfx_unload_scene(gfx);
	fd = init_data_loading(gfx, filename);
	if (!fd)
		return (0);
	if (!get_textures(gfx, fd) && (close(fd) || 1))
		return (0);
	if (!load_textures(gfx) && (close(fd) || 1))
		return (0);
	if (!get_sprites(gfx, fd) && (close(fd) || 1))
		return (0);
	result = get_map(gfx, fd);
	close(fd);
	if (!result)
		return (0);
	if (!validate_and_parse_map(&gfx->map))
		return (0);
	if (!parse_entities(gfx->map, &gfx->entities))
		return (0);
	set_player_variables(gfx);
	return (init_resources(gfx));
}
