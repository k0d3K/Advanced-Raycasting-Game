/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:34:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 16:45:26 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "config.h"
#include "rendering.h"
#include "libft.h"
#include "dt.h"
#include <math.h>

/**
 * @brief Moves a position by a certain amount in a given direction.
 * 
 * @param pos Initial position.
 * @param add Amount to move.
 * @param angle Direction to move.
 * 
 * @return New position vector.
 */
static t_vec2	move_player(t_vec2 pos, float add, float angle)
{
	pos.x += add * cosf(angle);
	pos.y += add * sinf(angle);
	return (pos);
}

/**
 * @brief This function handles the input of the player.
 * 
 * @param gfx The main structure of the program.
 */
static void	input_handling(t_gfx *gfx)
{
	t_input	input;
	t_vec2	*pos;
	t_vec2	last;
	float	*dir;

	input = gfx->input;
	pos = &gfx->player.pos;
	last = *pos;
	dir = &gfx->player.dir;
	if (input.up)
		*pos = move_player(*pos, PLAYER_SPEED * gfx->dt, *dir);
	if (input.left)
		*pos = move_player(*pos, PLAYER_SPEED * gfx->dt, *dir - PI / 2);
	if (input.down)
		*pos = move_player(*pos, PLAYER_SPEED * gfx->dt, *dir + PI);
	if (input.right)
		*pos = move_player(*pos, PLAYER_SPEED * gfx->dt, *dir + PI / 2);
	if (input.cam_left)
		*dir -= SPIN_SPEED * D2R * gfx->dt;
	if (input.cam_right)
		*dir += SPIN_SPEED * D2R * gfx->dt;
	if (vec2_length(*pos) > 2 * gfx->map.height + gfx->map.width)
		*pos = last;
}

static void	print_fps(t_gfx *gfx)
{
	int				sum;
	static int		arr[TARGET_FPS] = {0};
	static long		frame_count = 0;
	char			*str;
	int				i;

	arr[++frame_count % TARGET_FPS] = 1 / gfx->dt;
	sum = 0;
	i = 0;
	while (i < TARGET_FPS)
		sum += arr[i++];
	str = ft_itoa((int)(sum / TARGET_FPS));
	if (str)
		mlx_string_put(gfx->mlx, gfx->win, 10, 20, BLACK, str);
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
	input_handling(gfx);
	gfx->max_raycast_distance = vec2_length(gfx->player.pos) + sqrtf
		(gfx->map.height * gfx->map.height + gfx->map.width * gfx->map.width);
	render(gfx);
	gfx_render(gfx);
	delta_time_calculate(gfx);
	print_fps(gfx);
}
