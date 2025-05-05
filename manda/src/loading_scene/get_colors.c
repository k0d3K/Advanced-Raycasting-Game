/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:00:56 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/05 16:51:50 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "parsing.h"

static int	comma_count(char *line)
{
	char	c;
	int		count;

	c = *line++;
	count = 0;
	while (c)
	{
		count += c == ',';
		c = *line++;
	}
	return (count);
}

static int	parse_rgb(char **colors, t_color *out, char *colors_line)
{
	int	i;
	int	did_parse;
	int	rgb[3];

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_checked_atoi(colors[i], &did_parse);
		if (!did_parse || rgb[i] < 0 || rgb[i] > 255)
		{
			error(ERR_INVALID_RGB_FMT, colors_line);
			ft_clean_matrix((void **)colors);
			return (0);
		}
		i++;
	}
	*out = rgb[0] | rgb[1] << 8 | rgb[2] << 16;
	return (1);
}

static void	assign_color(t_identifiers id, t_color c, t_gfx *gfx)
{
	if (id == F)
		gfx->floor_col = c | 0xFF000000;
	else
		gfx->ceiling_col = c | 0xFF000000;
}

int	get_colors(t_gfx *gfx, t_identifiers id, char *colors_line)
{
	char	**colors;
	t_color	color;

	if (comma_count(colors_line) != 2)
	{
		error(ERR_INVALID_RGB_FMT, colors_line);
		return (0);
	}
	colors = ft_split(colors_line, ',');
	if (!colors || size_tab(colors) != 3)
	{
		if (!colors)
			error(ERR_MALLOC);
		else
		{
			error(ERR_INVALID_RGB_FMT, colors_line);
			ft_clean_matrix((void **)colors);
		}
		return (0);
	}
	if (!parse_rgb(colors, &color, colors_line))
		return (0);
	ft_clean_matrix((void **)colors);
	assign_color(id, color, gfx);
	return (1);
}
