/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:39:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/03/08 17:12:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include "utils.h"
#include "parsing.h"

static char	*get_line(int fd)
{
	char	*line;

	line = skip_empty_lines(fd);
	if (line == NULL)
	{
		error(ERR_INCOMPLETE_SCENE);
		return (NULL);
	}
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

static int	identify(char **id_and_args, int *num_texture)
{
	const char	*identifier[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	static int	loaded[6] = {0, 0, 0, 0, 0, 0};

	while (*num_texture < 6)
	{
		if (!ft_strcmp(id_and_args[0], (char *)identifier[*num_texture]))
			break ;
		(*num_texture)++;
	}
	if (*num_texture < 6 && loaded[*num_texture] == 1)
	{
		error(ERR_DOUBLE_ID, identifier[*num_texture]);
		return (0);
	}
	else if (*num_texture == 6)
	{
		error(ERR_IDENTIFIER, id_and_args[0]);
		return (0);
	}
	loaded[*num_texture] = 1;
	return (1);
}

static char	*get_info(char *line, int *num_texture)
{
	char	**id_and_args;
	char	*result;

	id_and_args = ft_split(line, ' ');
	if (!id_and_args || size_tab(id_and_args) != 2)
	{
		if (!id_and_args)
			error(ERR_MALLOC);
		else
		{
			error(ERR_INVALID_LINE, line);
			ft_clean_matrix((void **)id_and_args);
		}
		return (NULL);
	}
	if (!identify(id_and_args, num_texture))
	{
		ft_clean_matrix((void **)id_and_args);
		return (NULL);
	}
	result = id_and_args[1];
	free(id_and_args[0]);
	free(id_and_args);
	return (result);
}

static int	store_texture_or_color(t_gfx *gfx, int num_texture, char *arg)
{
	if (arg == NULL)
		return (0);
	if (num_texture < 4)
	{
		gfx->texture_files[num_texture] = arg;
		return (1);
	}
	else
	{
		if (!get_colors(gfx, (t_identifiers)num_texture, arg))
		{
			free(arg);
			return (0);
		}
		free(arg);
	}
	return (1);
}

int	get_textures(t_gfx *gfx, int fd)
{
	int		i;
	int		num_texture;
	char	*line;
	char	*arg;

	ft_bzero(gfx->texture_files, sizeof(gfx->texture_files));
	i = 0;
	while (i < 6)
	{
		line = get_line(fd);
		if (line == NULL)
			return (0);
		num_texture = 0;
		arg = get_info(line, &num_texture);
		free(line);
		if (!store_texture_or_color(gfx, num_texture, arg))
			return (0);
		i++;
	}
	return (1);
}
