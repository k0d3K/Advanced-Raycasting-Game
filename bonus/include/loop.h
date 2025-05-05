/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:15:47 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/26 18:19:29 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_H
# define LOOP_H

# include "gfx.h"

// loops
void	game_loop(t_gfx *gfx);
void	title_screen_loop(t_gfx *gfx);
void	end_screen_loop(t_gfx *gfx);

//	movements
void	manage_doors(t_gfx *gfx, int x, int y);
void	manage_entities(t_gfx *gfx);

//	debug / no_debug
void	debug_clear_window(t_gfx *gfx);
void	debug_render_map(t_gfx *gfx);
void	debug_render_map_post(t_gfx *gfx);

//	select_gun_img
void	choose_gun_img(t_gfx *gfx);

#endif
