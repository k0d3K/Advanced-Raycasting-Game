/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:46:59 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/18 19:18:03 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "geo.h"
# include <X11/keysym.h>
# include <stdint.h>

typedef struct s_input
{
	uint8_t	left;
	uint8_t	right;
	uint8_t	up;
	uint8_t	down;
	uint8_t	cam_left;
	uint8_t	cam_right;
	uint8_t	cam_up;
	uint8_t	cam_down;
	uint8_t	run;

	uint8_t	level_select_up;
	uint8_t	level_select_down;
	uint8_t	level_select_confirm;
}	t_input;

typedef struct s_gfx	t_gfx;

//	inputs
void	on_press(int keycode, t_gfx *gfx);
void	on_release(int keycode, t_gfx *gfx);

//	mouse
void	mouse_control(t_gfx *gfx, t_point cam_initial);
void	mouse_click(int button, int x, int y, t_gfx *gfx);

#endif
