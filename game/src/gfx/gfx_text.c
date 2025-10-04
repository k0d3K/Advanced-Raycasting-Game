/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:26:52 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 18:15:47 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "gfx.h"
#include <stdint.h>
#include <assert.h>

#define N_COLUMNS	16
#define N_ROWS		6
#define FIRST		'!'
#define LAST		'~'
#define DEFAULT		'?'

static __always_inline
	uint8_t	get_char_index(char c)
{
	if (c > LAST)
		c = DEFAULT;
	else if (c < FIRST)
		c = DEFAULT;
	return (c - FIRST);
}

int	gfx_text_init(t_gfx *gfx, char *font_path)
{
	char	*err;
	t_atlas	*font;

	font = &gfx->textures.font;
	err = atlas_init(gfx, font, font_path, (t_point){{N_COLUMNS, N_ROWS}});
	if (err)
		error(ERR_FAILED_TO_LOAD, font_path, err);
	return (!err);
}

static int	handle_special_character(
	char c, t_point *p, t_atlas *font, int orig_x_pos)
{
	if (c == '\n')
	{
		p->y += font->tile_height;
		p->x = orig_x_pos;
	}
	else if (c == ' ')
	{
		p->x += font->tile_width;
	}
	else
		return (0);
	return (1);
}

void	img_text(t_gfx *gfx, t_img *img, t_point p, char *str)
{
	t_atlas		*font;
	char		c;
	int			orig_x_pos;

	assert(gfx->textures.font.img.data != NULL);
	font = &gfx->textures.font;
	orig_x_pos = p.x;
	c = *str++;
	while (c)
	{
		if (!handle_special_character(c, &p, font, orig_x_pos))
		{
			atlas_render(font, img, get_char_index(c), p);
			p.x += font->tile_width;
		}
		c = *str++;
	}
}

void	gfx_text(t_gfx *gfx, t_point p, char *str)
{
	img_text(gfx, gfx->screen, p, str);
}
