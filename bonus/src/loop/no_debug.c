/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:34:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/19 15:26:54 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

#ifndef DEBUG

void	debug_clear_window(t_gfx *gfx)
{
	(void)gfx;
}

void	debug_render_map(t_gfx *gfx)
{
	(void)gfx;
}

void	debug_render_map_post(t_gfx *gfx)
{
	(void)gfx;
}

#endif
