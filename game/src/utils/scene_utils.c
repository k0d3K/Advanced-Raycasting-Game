/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:50:23 by dath              #+#    #+#             */
/*   Updated: 2025/04/15 19:47:17 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "gfx.h"

int	get_wall_height(char c)
{
	int	height;

	height = c - '0';
	if (height < 0 || height > 9)
		height = -1;
	return (height);
}

t_img	*get_face_image(t_face face, t_gfx *gfx)
{
	t_img	*img;

	if (face == NORTH)
		img = &gfx->textures.nord;
	else if (face == SOUTH)
		img = &gfx->textures.south;
	else if (face == WEST)
		img = &gfx->textures.west;
	else if (face == EAST)
		img = &gfx->textures.east;
	else if (face == DOOR)
		img = &gfx->textures.door;
	else
		img = &gfx->textures.exit;
	return (img);
}
