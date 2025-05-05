/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:57:47 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/05 16:49:43 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dt.h"
#include "config.h"
#include "libft.h"
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/time.h>

#define SEC_MICRO	1000000UL

static inline __attribute__((always_inline)) uint64_t	get_time_micro(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + tv.tv_sec * SEC_MICRO);
}

static __always_inline uint64_t	*get_last_frame(void)
{
	static uint64_t	last_frame = 0;

	return (&last_frame);
}

static void	my_usleep(uint64_t micro)
{
	uint64_t	beginning;

	beginning = get_time_micro();
	while (get_time_micro() - beginning < micro)
		;
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
		my_usleep((uint64_t)(remaining * SEC_MICRO));
		gfx->dt = frame_interval;
	}
	*get_last_frame() = get_time_micro();
}
