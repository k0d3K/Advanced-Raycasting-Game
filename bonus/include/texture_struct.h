/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:15:47 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/21 19:16:30 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_STRUCT_H
# define TEXTURE_STRUCT_H

# ifndef TEXTURE_H
#  error do not directly include this file
# endif

# include "img.h"
# include "libft.h"

typedef struct s_textures
{
	t_img		nord;
	t_img		south;
	t_img		west;
	t_img		east;
	t_img		door;
	t_img		top;
	t_img		sky;
	t_img		exit;
	t_atlas		*sprites;
	t_uint_list	size_sprites;
	t_img		heart;
	t_atlas		font;
	t_atlas		gun;
	t_img		bullet;
}	t_textures;

# define N_TEXTURES	8

#endif
