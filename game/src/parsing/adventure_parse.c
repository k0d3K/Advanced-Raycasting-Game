/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adventure_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:51:35 by dath              #+#    #+#             */
/*   Updated: 2025/04/28 15:30:26 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "parsing.h"
#include "gfx.h"
#include "bitmap.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/fcntl.h>

int	av_raise_error(t_adventure_parse_vars *v, char *fmt, ...)
{
	va_list	va;

	va_start(va, fmt);
	if (fmt)
	{
		ft_putstr_fd(ERROR_TEXT, 2);
		vfprintf(stderr, fmt, va);
		ft_putchar_fd('\n', 2);
	}
	va_end(va);
	close(v->fd);
	free(v->line);
	free(v->trimmed);
	str_list_free(&v->res->map_lst);
	dict_free(&v->res->properties);
	return (0);
}

static int	adventure_parse_line(char *line, t_adventure_parse_vars *v)
{
	char	*sep;

	if (!line || !*line)
		return (!!line || av_raise_error(v, ERR_MALLOC));
	if (*line == '[')
		return (av_handle_brackets(v, line));
	if (v->in_map_list)
		return (av_parse_map_entry(v, line));
	sep = ft_strchr(line, '=');
	if (!sep || sep == line || sep != ft_strrchr(line, '='))
		return (av_raise_error(v, "Invalid line: %s", line));
	return (av_parse_prop(v, line, sep));
}

static int	adventure_parse_loop(t_adventure_parse_vars *v)
{
	if (v->line[ft_strlen(v->line) - 1] == '\n')
		v->line[ft_strlen(v->line) - 1] = '\0';
	v->trimmed = ft_strtrim(v->line, " ");
	if (!adventure_parse_line(v->trimmed, v))
		return (0);
	free(v->line);
	free(v->trimmed);
	v->line = skip_empty_lines(v->fd);
	return (1);
}

static int	adventure_load_resources(t_gfx *gfx, t_adventure *adv)
{
	const void	*textures_to_load[] = {
		"start_screen", &adv->start_screen,
		"level_end_screen", &adv->level_end_screen,
		"end_screen", &adv->end_screen,
		"death_screen", &adv->death_screen};
	size_t		i;
	char		*to_load;
	char		*failed;

	i = 0;
	while (i < sizeof(textures_to_load) / sizeof(textures_to_load[0]))
	{
		to_load = dict_fetch(&adv->properties, (void *)textures_to_load[i]);
		if (to_load)
		{
			failed = bitmap_load(gfx, (void *)textures_to_load[i + 1], to_load);
			if (failed)
			{
				error(ERR_FAILED_TO_LOAD, to_load, failed);
				return (0);
			}
		}
		i += 2;
	}
	return (1);
}

int	adventure_parse(t_gfx *gfx, char *file, t_adventure *adventure)
{
	t_adventure_parse_vars	v;

	if (!dict_init(&adventure->properties, 1)
		|| !str_list_init(&adventure->map_lst, 50, 1))
	{
		dict_free(&adventure->properties);
		error(ERR_MALLOC);
		return (0);
	}
	ft_bzero(&v, sizeof(t_adventure_parse_vars));
	v.res = adventure;
	v.fd = open(file, O_RDONLY);
	if (v.fd < 0)
		return (av_raise_error(&v, ERR_OPEN, file));
	v.line = skip_empty_lines(v.fd);
	while (v.line)
		if (!adventure_parse_loop(&v))
			return (0);
	v.trimmed = NULL;
	v.line = NULL;
	if (v.in_map_list)
		return (av_raise_error(&v, "File ended while map list wasn't closed"));
	close(v.fd);
	return (adventure_load_resources(gfx, adventure));
}
