/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:39:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/16 19:51:28 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"

static void	print_erroneous_arg(char **args, char *result)
{
	if (!ft_strcmp(result, args[0]))
		error("The identifier %s is not attached to a textrure", result);
	else
		error("Invalid float number: %s", result);
}

static char	*get_pos_and_size(t_entity *entity, char **args)
{
	t_vec2		point;

	point.x = my_atof(args[1]);
	if (point.x == -1)
		return (args[1]);
	point.y = my_atof(args[2]);
	if (point.y == -1)
		return (args[2]);
	entity->pos = vec3(point.x, point.y, 0);
	entity->height = my_atof(args[3]);
	if (entity->height == -1)
		return (args[3]);
	entity->width = my_atof(args[4]);
	if (entity->width == -1)
		return (args[4]);
	return (NULL);
}

static char	*store_entity(t_gfx *gfx, char **args)
{
	t_entity	entity;
	int			pos_texture;
	char		*err;

	ft_bzero(&entity, sizeof(entity));
	if (!dict_contains_key(&gfx->texture_files, args[0]))
		return (args[0]);
	if (!ft_strcmp(args[0], "CO"))
		entity.type = T_COIN;
	else
		entity.type = T_ENEMY;
	pos_texture = dict_indexof(&gfx->texture_files, args[0]);
	entity.atlas = gfx->textures.sprites + pos_texture;
	err = get_pos_and_size(&entity, args);
	if (err)
		return (err);
	entity.whole_position = point(entity.plane_pos.x, entity.plane_pos.y);
	entity.need_to_refresh_pathfinding = 1;
	entity.life_point = 50 * (entity.height + entity.width);
	entity_add(gfx, entity);
	return (NULL);
}

int	get_sprites_infos(int fd, char ***args)
{
	char	*line;

	line = get_line(fd);
	if (line == NULL)
		return (0);
	if (!ft_strcmp(line, "MAP"))
	{
		free(line);
		return (0);
	}
	*args = get_sprite_line_infos(line);
	free(line);
	return (1);
}

int	get_sprites(t_gfx *gfx, int fd)
{
	char	**args;
	char	*result;

	while (1)
	{
		args = NULL;
		if (!get_sprites_infos(fd, &args))
			break ;
		if (!args)
			return (0);
		result = store_entity(gfx, args);
		if (result)
		{
			print_erroneous_arg(args, result);
			ft_clean_matrix((void **)args);
			return (0);
		}
		ft_clean_matrix((void **)args);
	}
	if (!gfx->entities.arr)
	{
		error(ERR_MALLOC);
		return (0);
	}
	return (1);
}
