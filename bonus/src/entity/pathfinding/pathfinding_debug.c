/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_debug.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:46:21 by dath              #+#    #+#             */
/*   Updated: 2025/04/29 19:27:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinding.h"
#include "gfx.h"

#ifdef DEBUG

void	pf_debug_show_line(t_gfx *gfx, t_point start, t_point end)
{
	const t_point	p = {{
		TRUE_WIN_W + start.x * UI_SCALE + UI_SCALE / 2,
		start.y * UI_SCALE + UI_SCALE / 2
	}};
	const t_point	ep = {{
		TRUE_WIN_W + end.x * UI_SCALE + UI_SCALE / 2,
		end.y * UI_SCALE + UI_SCALE / 2
	}};

	gfx_line(gfx, p, ep, CYAN);
}

#else

void	pf_debug_show_line(t_gfx *gfx, t_point start, t_point end)
{
	(void)gfx;
	(void)start;
	(void)end;
}

#endif
