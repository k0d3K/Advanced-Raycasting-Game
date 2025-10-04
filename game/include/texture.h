/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:03:09 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/26 12:27:10 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "texture_struct.h"

typedef struct s_gfx	t_gfx;

int		load_textures(t_gfx *gfx);
void	unload_textures(t_gfx *gfx);
int		load_static_textures(t_gfx *gfx);
void	unload_static_textures(t_gfx *gfx);

#endif