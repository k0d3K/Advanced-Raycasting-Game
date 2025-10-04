/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:36:53 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/29 19:27:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"
#include "utils.h"
#include "rendering.h"
#include <X.h>
#include <string.h>
#include <errno.h>

static int	init_screens(t_gfx *gfx)
{
	if (!img_init(gfx, &gfx->screen1, point(WIN_W, WIN_H)))
		return (0);
	if (!img_init(gfx, &gfx->screen2, point(WIN_W, WIN_H)))
		return (0);
	if (!img_init(gfx, &gfx->minimap_img,
			point(MMAP_RADIUS * 2, MMAP_RADIUS * 2)))
		return (0);
	if (!img_init(gfx, &gfx->stats_img, point(TRUE_WIN_W, WIN_H)))
		return (0);
	if (!img_init(gfx, &gfx->hurt_img, point(TRUE_WIN_W, WIN_H)))
		return (0);
	gfx->screen = &gfx->screen1;
	gfx->back = &gfx->screen2;
	return (1);
}

static int	init_render_thread(t_gfx *gfx, int i)
{
	gfx->render_threads[i].gfx = gfx;
	gfx->render_threads[i].id = i;
	gfx->render_threads[i].lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	gfx->render_threads[i].thread_initialized = 0;
	if (pthread_create(&gfx->render_threads[i].thread,
			NULL, (void *)render_thread, &gfx->render_threads[i]))
	{
		set_thread_state(gfx, STATE_ABORT);
		join_threads(gfx, i);
		free(gfx->render_threads);
		gfx->render_threads = NULL;
		return (0);
	}
	return (1);
}

static int	init_threads(t_gfx *gfx, int i)
{
	gfx->render_threads = ft_calloc(sizeof(t_render_thread), N_THREADS);
	if (!gfx->render_threads)
		return (0);
	gfx->render_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	gfx->thread_state_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	gfx->thread_state = STATE_INITIALIZING;
	while (i < N_THREADS)
	{
		if (!init_render_thread(gfx, i++))
			return (0);
	}
	set_thread_state(gfx, STATE_RUNNING);
	i = 0;
	while (i < N_THREADS)
	{
		while (1)
		{
			pthread_mutex_lock(&gfx->render_threads[i].lock);
			if (gfx->render_threads[i].thread_initialized)
				break ;
			pthread_mutex_unlock(&gfx->render_threads[i].lock);
		}
		pthread_mutex_unlock(&gfx->render_threads[i++].lock);
	}
	return (1);
}

int	gfx_init(t_gfx *gfx)
{
	if (!load_static_textures(gfx))
		return (0);
	if (!init_screens(gfx))
	{
		error(MLX_IMG_FAIL);
		return (0);
	}
	if (!init_threads(gfx, 0))
	{
		error(ERR_PTHREAD_CREATE, strerror(errno));
		return (0);
	}
	return (1);
}
