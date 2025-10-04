/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_screen_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:15:45 by dath              #+#    #+#             */
/*   Updated: 2025/04/29 18:31:49 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include <stdio.h>

void	put_img_on_whole_screen(t_gfx *gfx, t_img img);

static int	has_played_last_level(t_gfx *gfx)
{
	t_game_vars	*vars;

	vars = &gfx->game_vars;
	return ((vars->single_level
			|| (size_t)vars->level_index == vars->adventure.map_lst.len - 1));
}

static int	handle_input(t_gfx *gfx)
{
	if (gfx->input.level_select_confirm && gfx->time_elapsed > 3)
	{
		if (has_played_last_level(gfx) || gfx->game_vars.player_died)
		{
			mlx_loop_end(gfx->mlx);
			ft_printf("Thanks for playing !! See you later loser\n");
		}
		else
			load_next_level(gfx, 0);
		return (1);
	}
	return (0);
}

#define BUF_LEN	150

static void	fill_text_buffer(t_gfx *gfx, char buf[BUF_LEN])
{
	t_game_vars	*vars;
	int			length;

	vars = &gfx->game_vars;
	if (vars->player_died)
		length = snprintf(buf, BUF_LEN,
				"You died, sucker !!");
	else if (vars->single_level)
		length = snprintf(buf, BUF_LEN,
				"Level completed !");
	else
		length = snprintf(buf, BUF_LEN,
				"Level %d completed !", vars->level_index + 1);
	if (gfx->time_elapsed > 1.5f)
		length += snprintf(buf + length, BUF_LEN - length,
				"\nTook %.02f seconds.", vars->time_taken_in_level);
	if (gfx->time_elapsed > 3)
	{
		if (has_played_last_level(gfx) || gfx->game_vars.player_died)
			length += snprintf(buf + length, BUF_LEN - length,
					"\nThanks for playing !!");
		length += snprintf(buf + length, BUF_LEN - length,
				"\nPress ENTER to continue.");
	}
}

void	end_screen_loop(t_gfx *gfx)
{
	char		buf[BUF_LEN];

	if (handle_input(gfx))
		return ;
	clear_img(gfx->screen, BLACK);
	if (gfx->game_vars.adventure.end_screen.mlx_img)
	{
		if (gfx->game_vars.player_died)
			put_img_on_whole_screen(gfx,
				gfx->game_vars.adventure.death_screen);
		else if (has_played_last_level(gfx))
			put_img_on_whole_screen(gfx,
				gfx->game_vars.adventure.end_screen);
		else
			put_img_on_whole_screen(gfx,
				gfx->game_vars.adventure.level_end_screen);
	}
	fill_text_buffer(gfx, buf);
	gfx_text(gfx, (t_point){{0, 0}}, buf);
	gfx_render(gfx);
}
