/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_gun_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:33:01 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:31:36 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "gfx.h"

static void	choose_reloading_img(t_gfx *gfx, uint64_t elapsed, uint64_t current)
{
	if (elapsed > 100000 && elapsed < 200000)
		gfx->gun.n_gun_img = 4;
	else if (elapsed > 200000 && elapsed < 300000)
		gfx->gun.n_gun_img = 5;
	else if (elapsed > 300000 && elapsed < 400000)
		gfx->gun.n_gun_img = 4;
	else if (elapsed > 400000 && elapsed < 500000)
		gfx->gun.n_gun_img = 3;
	else if (elapsed > 500000)
	{
		gfx->gun.last_shot = current;
		gfx->gun.n_gun_img = 0;
		gfx->gun.reloading = 0;
		gfx->gun.nb_shot_left = 5;
	}
}

void	choose_gun_img(t_gfx *gfx)
{
	uint64_t	current;
	uint64_t	elapsed;

	current = get_time_micro();
	elapsed = current - gfx->gun.last_shot;
	if (gfx->gun.reloading)
		choose_reloading_img(gfx, elapsed, current);
	else if (gfx->gun.n_gun_img == 1 && elapsed > 50000 && elapsed < 130000)
		gfx->gun.n_gun_img = 2;
	else if (gfx->gun.n_gun_img == 2 && elapsed > 130000)
		gfx->gun.n_gun_img = 1;
	else if (gfx->gun.n_gun_img == 1 && elapsed > 200000)
	{
		gfx->gun.last_shot = current;
		gfx->gun.n_gun_img = 0;
	}
}
