/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:34:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/26 18:21:40 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "libft.h"
#include "dt.h"

/**
 * @brief This function prints the FPS on the screen.
 * 
 * @param gfx The main structure of the program.
 */
static void	print_fps(t_gfx *gfx)
{
	static int		arr[50] = {0};
	static long		frame_count = 0;
	char			*str;
	int				sum;
	int				i;

	arr[++frame_count % 50] = 1 / gfx->dt;
	sum = 0;
	i = 0;
	while (i < 50)
		sum += arr[i++];
	str = ft_itoa((int)(sum / 50));
	if (str)
		mlx_string_put(gfx->mlx, gfx->win, 10, 20, RED, str);
	free(str);
}

/**
 * @brief This function is the main loop of the program.
 * 		It is called every frame.
 * 
 * @param gfx The main structure of the program.
 */
void	loop(t_gfx *gfx)
{
	if (gfx->game_vars.game_state == IN_TITLE_SCREEN)
		title_screen_loop(gfx);
	else if (gfx->game_vars.game_state == IN_LEVEL_END_SCREEN)
		end_screen_loop(gfx);
	else
		game_loop(gfx);
	delta_time_calculate(gfx);
	print_fps(gfx);
}
