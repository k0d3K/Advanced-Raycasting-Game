/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:57:09 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/11 15:34:57 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "gfx.h"

//	minimap.c
void	render_map(t_gfx *gfx);

//	minimap_drawing.c
void	mmap_draw_player(t_gfx *gfx);
void	mmap_draw_entities(t_gfx *gfx, unsigned int i);

//	minimap_utils.c
t_point	map_calc_pos_on_mmap(t_gfx *gfx, t_entity entity);
t_vec2	mmap_calc_pos_on_map(t_gfx *gfx, t_point minimap_pxl, t_vec2 dir);
void	mmap_put_avg(t_gfx *gfx, t_point pos);

void	render_stats(t_gfx *gfx);
#endif
