/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:38:07 by dath              #+#    #+#             */
/*   Updated: 2025/05/05 15:34:07 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "strings.h"
#include "utils.h"
#include "texture.h"

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char	*get_line(int fd)
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

char	**get_sprite_line_infos(char *line)
{
	char	**id_and_args;

	id_and_args = ft_split(line, ' ');
	if (!id_and_args || size_tab(id_and_args) != 5)
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
	return (id_and_args);
}

char	**get_texture_line_infos(char *line)
{
	const char	*ids[N_TEXTURES] = {"NO", "SO", "WE", "EA", "DO",
		"F", "C", "e"};
	char		**args;
	int			id;
	int			found;

	args = ft_split(line, ' ');
	if (!args)
		error(ERR_MALLOC);
	id = 0;
	found = 0;
	while (id < N_TEXTURES)
	{
		if (!ft_strcmp(args[0], (char *)ids[id]))
			found = 1;
		id++;
	}
	if ((found && size_tab(args) != 2) || (!found && size_tab(args) != 4))
	{
		error(ERR_INVALID_LINE, line);
		ft_clean_matrix((void **)args);
		return (NULL);
	}
	return (args);
}
