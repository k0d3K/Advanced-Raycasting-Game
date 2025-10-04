/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_remaining_text.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:11 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 18:59:44 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include <stdio.h>

void	render_remaining_text(t_gfx *gfx)
{
	char			buf[50];
	const t_point	pos = point(0, WIN_H - gfx->textures.font.tile_height * 2);

	snprintf(buf, sizeof(buf), "%d/%d\n%d/%d",
		gfx->game_vars.n_coins_collected, gfx->game_vars.n_coins,
		gfx->game_vars.n_enemies_killed, gfx->game_vars.n_enemies);
	img_text(gfx, &gfx->stats_img, pos, buf);
}
