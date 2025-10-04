/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adventure_parse_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:04:24 by dath              #+#    #+#             */
/*   Updated: 2025/04/27 14:59:53 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static void	rtrim_spaces(char *s)
{
	size_t	sz;
	char	*ptr;

	sz = ft_strlen(s);
	ptr = s + sz - 1;
	while (ptr > s && *ptr == ' ')
		ptr--;
	*(ptr + 1) = '\0';
}

int	av_parse_prop(t_adventure_parse_vars *v, char *line, char *sep)
{
	char	*key;
	char	*value;

	if (v->res->properties.hash_list.len == v->res->properties.hash_list.cap)
		return (av_raise_error(v, "Too many attributes in file"));
	key = ft_substr(line, 0, sep - line);
	if (!key)
		return (av_raise_error(v, ERR_MALLOC));
	rtrim_spaces(key);
	if (!*key)
	{
		free(key);
		return (av_raise_error(v, "Empty property key"));
	}
	value = ft_strdup(sep + 1);
	if (!value)
	{
		free(key);
		return (av_raise_error(v, ERR_MALLOC));
	}
	dict_add(&v->res->properties, key, value);
	free(key);
	return (1);
}

int	av_parse_map_entry(t_adventure_parse_vars *v, char *line)
{
	char	*map_name;

	if (v->res->map_lst.len == v->res->map_lst.cap)
		return (av_raise_error(v, "Too many maps in file"));
	map_name = ft_strdup(line);
	if (!map_name)
		return (av_raise_error(v, ERR_MALLOC));
	if (!ft_strends_with(map_name, ".cub"))
	{
		free(map_name);
		return (av_raise_error(v,
				"Map file doesn't end with .cub: %s", line));
	}
	if (access(map_name, R_OK))
	{
		free(map_name);
		return (av_raise_error(v, "Map file does not exist: %s", line));
	}
	str_list_add(&v->res->map_lst, map_name);
	return (1);
}

int	av_handle_brackets(t_adventure_parse_vars *v, char *line)
{
	if (!ft_strncmp(line, "[map_list]", sizeof("[map_list]") - 1))
	{
		v->in_map_list = !v->in_map_list;
		if (!v->in_map_list || v->parsed_map_list)
			return (av_raise_error(v, "attribute '[map_list] set twice'"));
		return (1);
	}
	if (!ft_strncmp(line, "[end]", sizeof("[end]") - 1))
	{
		if (!v->in_map_list)
			return (av_raise_error(v, "attribute '[end]' not set correctly"));
		if (!v->res->map_lst.len)
			return (av_raise_error(v, "no map in [map_list]"));
		v->in_map_list = !v->in_map_list;
		v->parsed_map_list = 1;
		return (1);
	}
	return (av_raise_error(v, "Invalid '[' attribute: %s", line));
}
