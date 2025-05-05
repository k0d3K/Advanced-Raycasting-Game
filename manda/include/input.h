/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:46:59 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/18 18:35:15 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

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
}	t_input;

typedef struct s_gfx	t_gfx;

void	on_press(int keycode, t_gfx *gfx);
void	on_release(int keycode, t_gfx *gfx);

#endif
