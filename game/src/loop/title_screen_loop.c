/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_screen_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:15:47 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 17:12:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include <sys/param.h>

void	put_img_on_whole_screen(t_gfx *gfx, t_img img)
{
	t_point	p;
	t_vec2	scale_ratioes;
	t_color	c;
	t_color	*data;

	p.y = 0;
	scale_ratioes = vec2(
			(float)img.size.x / WIN_W, (float)img.size.y / WIN_H);
	data = gfx->screen->data;
	while (p.y < WIN_H)
	{
		p.x = 0;
		while (p.x < WIN_W)
		{
			c = *(img.data
					+ img.size.x * (int)(scale_ratioes.y * p.y)
					+ (int)(scale_ratioes.x * p.x));
			*data++ = c;
			p.x++;
		}
		p.y++;
	}
}

static void	handle_level_cursor(t_gfx *gfx)
{
	t_game_vars	*vars;

	vars = &gfx->game_vars;
	gfx->input.level_select_confirm = 0;
	if (gfx->input.level_select_up)
	{
		vars->level_cursor = MIN(
				vars->level_cursor + 1, (int)vars->adventure.map_lst.len - 1);
		gfx->input.level_select_up = 0;
	}
	if (gfx->input.level_select_down)
	{
		vars->level_cursor = MAX(vars->level_cursor - 1, 0);
		gfx->input.level_select_down = 0;
	}
}

void	title_screen_loop(t_gfx *gfx)
{
	t_game_vars	*vars;

	if (gfx->input.level_select_confirm && gfx->time_elapsed > 0.9f)
	{
		load_next_level(gfx, 1);
		return ;
	}
	handle_level_cursor(gfx);
	vars = &gfx->game_vars;
	if (vars->adventure.start_screen.mlx_img)
		put_img_on_whole_screen(gfx, vars->adventure.start_screen);
	else
		clear_img(gfx->screen, BLACK);
	gfx_text(gfx,
		point(500, 500), vars->adventure.map_lst.arr[vars->level_cursor]);
	gfx_render(gfx);
}
