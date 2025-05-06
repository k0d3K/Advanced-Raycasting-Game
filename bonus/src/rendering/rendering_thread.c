/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:13:15 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 14:44:55 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "gfx.h"
#include "utils.h"
#include "minimap.h"
#include <sys/time.h>
#include <errno.h>

static int	wait_for_cond(t_render_thread *self)
{
	t_gfx			*gfx;

	gfx = self->gfx;
	self->thread_initialized = 1;
	pthread_cond_wait(&gfx->render_cond, &self->lock);
	if (get_thread_state(gfx) == STATE_STOP)
		return (0);
	return (1);
}

void	render_loop(t_render_thread *self)
{
	t_point	range;

	range.x = self->id * N_PIXEL_PER_SLICE;
	range.y = range.x + N_PIXEL_PER_SLICE;
	if (range.y > TRUE_WIN_W)
		range.y = TRUE_WIN_W;
	while (1)
	{
		if (!wait_for_cond(self))
			break ;
		render(self, range.x, range.y);
		if (N_THREADS <= 1)
			render_map(self->gfx);
		if (N_THREADS <= 2)
			render_stats(self->gfx);
		self->frame_rendered = 1;
	}
}

void	minimap_render_loop(t_render_thread *self)
{
	while (1)
	{
		if (!wait_for_cond(self))
			break ;
		render_map(self->gfx);
		self->frame_rendered = 1;
	}
}

void	stats_render_loop(t_render_thread *self)
{
	while (1)
	{
		if (!wait_for_cond(self))
			break ;
		render_stats(self->gfx);
		self->frame_rendered = 1;
	}
}

void	*render_thread(t_render_thread *self)
{
	t_gfx	*gfx;

	gfx = self->gfx;
	while (get_thread_state(gfx) == STATE_INITIALIZING)
		ft_usleep(20);
	if (get_thread_state(gfx) == STATE_ABORT)
		return (NULL);
	pthread_mutex_lock(&self->lock);
	if (N_THREADS > 1 && self->id == N_THREADS - 1)
		minimap_render_loop(self);
	else if (N_THREADS > 2 && self->id == N_THREADS - 2)
		stats_render_loop(self);
	else
		render_loop(self);
	pthread_mutex_unlock(&self->lock);
	return (NULL);
}
