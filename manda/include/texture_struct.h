/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:15:47 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 17:14:00 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_STRUCT_H
# define TEXTURE_STRUCT_H

# ifndef TEXTURE_H
#  error do not directly include this file
# endif

# include "img.h"

typedef struct s_textures
{
	t_img	nord;
	t_img	south;
	t_img	west;
	t_img	east;
}	t_textures;

#endif
