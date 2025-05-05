/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:29:17 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 14:09:12 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "gfx.h"
#include "libft.h"
#include "utils.h"
#include "bitmap.h"
#include <assert.h>
#include <stdarg.h>

static char	*load_textures_batch(t_gfx *gfx, char **err)
{
	size_t	i;
	t_img	*ptr;
	char	*cur;
	char	**filenames;

	i = 0;
	ptr = (t_img *)&gfx->textures;
	filenames = gfx->texture_files;
	while (i < (sizeof(t_textures) / sizeof(t_img)))
	{
		cur = filenames[i];
		*err = bitmap_load(gfx, &ptr[i], cur);
		if (*err)
			return (cur);
		i++;
	}
	*err = NULL;
	return (NULL);
}

void	unload_textures(t_gfx *gfx)
{
	size_t	i;
	t_img	*ptr;

	i = 0;
	ptr = (t_img *)&gfx->textures;
	while (i < (sizeof(t_textures) / sizeof(t_img)))
	{
		if (ptr[i].mlx_img)
			mlx_destroy_image(gfx->mlx, ptr[i].mlx_img);
		i++;
	}
	i = 0;
	while (i < sizeof(gfx->texture_files) / sizeof(char *))
		free(gfx->texture_files[i++]);
	ft_bzero(&gfx->textures, sizeof(t_textures));
}

int	load_textures(t_gfx *gfx)
{
	const char	*failed;
	char		*err;

	failed = load_textures_batch(gfx, &err);
	if (failed)
	{
		error(ERR_FAILED_TO_LOAD, failed, err);
		return (0);
	}
	return (1);
}
