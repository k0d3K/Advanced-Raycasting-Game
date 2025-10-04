/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:39:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/06 17:40:40 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include "utils.h"
#include "parsing.h"

static	int	is_int(char *str)
{
	int	i;
	int	success;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	i = ft_checked_atoi(str, &success);
	if (!success || i > 100)
		return (-1);
	return (i);
}

static	int	get_atlas_size(t_gfx *gfx, char **args)
{
	int			x;
	int			y;
	uint32_t	size;

	x = is_int(args[2]);
	y = is_int(args[3]);
	if (x <= 0 || y <= 0)
	{
		if (x <= 0)
			error(ERR_ATLAS_SIZE, args[2]);
		else
			error(ERR_ATLAS_SIZE, args[3]);
		ft_clean_matrix((void **)args);
		args = NULL;
		return (0);
	}
	size = (int16_t)x << 16 | (int16_t)y;
	uint_list_add(&gfx->textures.size_sprites, size);
	free(args[2]);
	free(args[3]);
	return (1);
}

static int	store_texture(t_gfx *gfx, char **args)
{
	if (dict_contains_key(&gfx->texture_files, args[0]))
	{
		error(ERR_DOUBLE_ID, args[0]);
		ft_clean_matrix((void **)args);
		args = NULL;
		return (0);
	}
	if (args[2] && !get_atlas_size(gfx, args))
		return (0);
	dict_add(&gfx->texture_files, args[0], args[1]);
	free(args[0]);
	free(args);
	return (1);
}

int	check_missing_identifiers(t_gfx *gfx)
{
	const char	*identifiers[N_TEXTURES] = {"NO", "SO", "WE", "EA", "DO",
		"F", "C", "e"};
	int			id;

	if (!gfx->textures.size_sprites.arr || !gfx->texture_files.main_list.arr)
	{
		error(ERR_MALLOC);
		return (0);
	}
	id = 0;
	while (id < N_TEXTURES)
	{
		if (!dict_contains_key(&gfx->texture_files, (char *)identifiers[id]))
		{
			error("Missing identifier: %s", (char *)identifiers[id]);
			return (0);
		}
		id++;
	}
	return (1);
}

int	get_textures(t_gfx *gfx, int fd)
{
	char	*line;
	char	**args;
	int		result;

	while (1)
	{
		line = get_line(fd);
		if (line == NULL)
			return (0);
		if (!ft_strcmp(line, "ENTITY"))
		{
			free(line);
			break ;
		}
		args = get_texture_line_infos(line);
		free(line);
		if (!args)
			return (0);
		result = store_texture(gfx, args);
		if (!result)
			return (0);
	}
	if (!check_missing_identifiers(gfx))
		return (0);
	return (1);
}
