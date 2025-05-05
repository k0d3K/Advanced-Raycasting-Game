/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:57:47 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 15:44:44 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dt.h"
#include "utils.h"
#include <stdint.h>
#include <sys/cdefs.h>

static __always_inline uint64_t	*get_last_frame(void)
{
	static uint64_t	last_frame = 0;

	return (&last_frame);
}

void	delta_time_init(void)
{
	*get_last_frame() = get_time_micro();
}

void	delta_time_calculate(t_gfx *gfx)
{
	const float	frame_interval = 1.0f / (float)TARGET_FPS;
	uint64_t	time_diff;
	float		remaining;

	time_diff = get_time_micro() - *get_last_frame();
	gfx->dt = (float)time_diff / (float)SEC_MICRO;
	if (gfx->dt < frame_interval)
	{
		remaining = frame_interval - gfx->dt;
		ft_usleep((uint64_t)(remaining * SEC_MICRO));
		gfx->dt = frame_interval;
	}
	gfx->time_elapsed += gfx->dt;
	*get_last_frame() = get_time_micro();
}
