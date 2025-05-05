/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:37:15 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/10 19:39:15 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include "dt.h"
#include "config.h"
#include "input.h"
#include "parsing.h"
#include "utils.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>

static void	pre_parsing(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		error(ERR_ARGC);
		exit(-1);
	}
	i = ft_strlen(argv[1]) - 1;
	if (argv[1][i] != 'b' || argv[1][i - 1] != 'u'
		|| argv[1][i - 2] != 'c' || argv[1][i - 3] != '.')
	{
		error(ERR_NEED_BER);
		exit(-1);
	}
}

static void	set_variables(t_gfx *gfx)
{
	gfx->tan_half_fov = tanf(g_aspect_ratio * (FOV * D2R) / 2);
	gfx->player.height = PLAYER_EYE;
}

int	main(int argc, char **argv)
{
	t_gfx	gfx;
	int		init;

	ft_bzero(&gfx, sizeof(t_gfx));
	pre_parsing(argc, argv);
	if (!load_data_from_file(&gfx, argv[1]))
	{
		gfx_deinit(&gfx);
		return (1);
	}
	init = gfx_init(&gfx);
	if (init)
	{
		mlx_loop_hook(gfx.mlx, (void *)loop, &gfx);
		mlx_hook(gfx.win, KeyPress, KeyPressMask, (void *)on_press, &gfx);
		mlx_hook(gfx.win, KeyRelease, KeyReleaseMask, (void *)on_release, &gfx);
		mlx_hook(gfx.win, DestroyNotify, 0, mlx_loop_end, gfx.mlx);
		delta_time_init();
		set_variables(&gfx);
		mlx_loop(gfx.mlx);
	}
	gfx_deinit(&gfx);
	return (!init);
}
