/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:31:51 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/28 15:31:50 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "dt.h"

void	toggle_level_end_screen(t_gfx *gfx, int died)
{
	gfx->game_vars.game_state = IN_LEVEL_END_SCREEN;
	gfx->game_vars.time_taken_in_level = gfx->time_elapsed;
	gfx_unload_scene(gfx);
	gfx->time_elapsed = 0;
	if (died)
		gfx->game_vars.player_died = 1;
}

void	load_next_level(t_gfx *gfx, int is_first_level)
{
	int	cursor;

	if (!is_first_level)
		++gfx->game_vars.level_cursor;
	cursor = gfx->game_vars.level_cursor;
	if (!load_data_from_file(gfx, gfx->game_vars.adventure.map_lst.arr[cursor]))
	{
		mlx_loop_end(gfx->mlx);
		return ;
	}
	gfx->game_vars.game_state = PLAYING;
	gfx->game_vars.level_index = cursor;
	gfx->time_elapsed = 0;
	delta_time_init();
}
