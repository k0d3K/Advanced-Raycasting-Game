/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:21:49 by dath              #+#    #+#             */
/*   Updated: 2025/04/18 13:58:57 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "rendering.h"
#include "gfx.h"
#include <pthread.h>

t_thread_state	get_thread_state(t_gfx *gfx)
{
	t_thread_state	state;

	pthread_mutex_lock(&gfx->thread_state_lock);
	state = gfx->thread_state;
	pthread_mutex_unlock(&gfx->thread_state_lock);
	return (state);
}

void	set_thread_state(t_gfx *gfx, t_thread_state state)
{
	pthread_mutex_lock(&gfx->thread_state_lock);
	gfx->thread_state = state;
	pthread_mutex_unlock(&gfx->thread_state_lock);
}

void	wait_until_all_slices_rendered(t_gfx *gfx)
{
	int	i;

	i = 0;
	while (i < N_THREADS)
	{
		while (1)
		{
			pthread_mutex_lock(&gfx->render_threads[i].lock);
			if (gfx->render_threads[i].frame_rendered)
				break ;
			pthread_mutex_unlock(&gfx->render_threads[i].lock);
		}
		gfx->render_threads[i].frame_rendered = 0;
		pthread_mutex_unlock(&gfx->render_threads[i++].lock);
	}
}

void	join_threads(t_gfx *gfx, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_join(gfx->render_threads[i++].thread, NULL);
}
