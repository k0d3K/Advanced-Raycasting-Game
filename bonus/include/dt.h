/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:56:16 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/13 16:10:17 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DT_H
# define DT_H

# include "gfx.h"

void	delta_time_init(void);
void	delta_time_calculate(t_gfx *gfx);

#endif
