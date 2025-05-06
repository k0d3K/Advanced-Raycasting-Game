/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:37:15 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 17:14:15 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include "dt.h"
#include "input.h"
#include "parsing.h"
#include "utils.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <sys/socket.h>

static void	pre_parsing(int argc, char **argv, t_game_vars *game_state)
{
	if (argc != 2)
	{
		error(ERR_ARGC);
		exit(-1);
	}
	if (ft_strends_with(argv[1], ".cub"))
		game_state->single_level = 1;
	else if (ft_strends_with(argv[1], ".adv"))
		game_state->game_state = IN_TITLE_SCREEN;
	else
	{
		error(ERR_INVALID_SUFFIX);
		exit(-1);
	}
}

static void	make_screens_black(t_gfx *gfx)
{
	int		i;
	t_color	*data;

	data = gfx->screen1.data;
	i = -1;
	while (++i < WIN_W * WIN_H)
		*data++ = BLACK;
	data = gfx->screen2.data;
	i = -1;
	while (++i < WIN_W * WIN_H)
		*data++ = BLACK;
}

static int	init_all_resources(t_gfx *gfx, char *arg)
{
	gfx->mlx = mlx_init();
	if (!gfx->mlx || !gfx_init(gfx))
	{
		error(MLX_INIT_FAIL);
		return (0);
	}
	if (gfx->game_vars.single_level && !load_data_from_file(gfx, arg))
		return (0);
	else if (!gfx->game_vars.single_level
		&& !adventure_parse(gfx, arg, &gfx->game_vars.adventure))
		return (0);
	gfx->win = mlx_new_window(gfx->mlx, WIN_W, WIN_H, "cub3D", 1);
	if (!gfx->win)
	{
		error(MLX_WIN_FAIL);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_gfx	gfx;

	ft_bzero(&gfx, sizeof(t_gfx));
	pre_parsing(argc, argv, &gfx.game_vars);
	if (!init_all_resources(&gfx, argv[1]))
	{
		gfx_deinit(&gfx);
		return (1);
	}
	mlx_mouse_hide(gfx.mlx, gfx.win);
	make_screens_black(&gfx);
	mlx_mouse_move(gfx.mlx, gfx.win, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(gfx.mlx, (void *)loop, &gfx);
	mlx_hook(gfx.win, KeyPress, KeyPressMask, (void *)on_press, &gfx);
	mlx_hook(gfx.win, KeyRelease, KeyReleaseMask, (void *)on_release, &gfx);
	mlx_hook(gfx.win, DestroyNotify, 0, mlx_loop_end, gfx.mlx);
	mlx_mouse_hook(gfx.win, (void *)mouse_click, &gfx);
	delta_time_init();
	sort_entities_by_dist(&gfx, gfx.player.plane_pos);
	mlx_loop(gfx.mlx);
	gfx_deinit(&gfx);
	return (0);
}
