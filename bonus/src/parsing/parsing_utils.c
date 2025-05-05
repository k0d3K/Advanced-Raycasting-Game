/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:39:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/04/16 12:19:28 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"

float	my_atof(const char *str)
{
	float	result;
	float	fraction;

	fraction = 0.1f;
	result = 0.0f;
	while (*str && *str != '.')
	{
		if (((*str < '0' || *str > '9') && *str != '.'))
			return (-1);
		result = result * 10.0f + (*str - '0');
		str++;
	}
	if (!str)
		return (result);
	str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		result += (*str - '0') * fraction;
		fraction *= 0.1f;
		str++;
	}
	return (result);
}

void	print_erroneous_line(t_map *map, int x, int y, char *err)
{
	char	*line;
	int		i;

	error(err);
	if (!ft_strcmp(err, ERR_PLAYER_NOT_FOUND))
		return ;
	i = 0;
	line = map->map[y];
	if (!line || x > (int)ft_strlen(line))
		return ;
	if (y > 0)
		ft_putendl_fd(map->map[y - 1], 2);
	while (i < x)
		write(2, &line[i++], 1);
	write(2, CONSOLE_RED, sizeof(CONSOLE_RED));
	write(2, &line[i++], 1);
	write(2, CONSOLE_RESET, sizeof(CONSOLE_RESET));
	while (i < map->width)
		write(2, &line[i++], 1);
	write(2, "\n", 1);
	while (x-- > 0)
		write(2, " ", 1);
	write(2, UNICODE_ARROW "\n", sizeof(UNICODE_ARROW "\n"));
	if (y + 1 < map->height)
		ft_putendl_fd(map->map[y + 1], 2);
}
