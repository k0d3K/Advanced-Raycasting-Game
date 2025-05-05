/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:38:26 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 12:38:07 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define WIN_X			1920
# define WIN_Y			1080
# define WIN_TITLE		"cub3D"
# define TARGET_FPS		120

static const float	g_aspect_ratio = (float)WIN_Y / WIN_X;

# define UI_SCALE		30
# define FOV			60.0f
# define WALL_HEIGHT	1.0f
# define PLAYER_EYE		0.5f 
# define PLAYER_SPEED	3.0f
# define SPIN_SPEED		60.0f

#endif