/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_deinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:45:12 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 13:35:23 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static void	unload_textures_2(t_gfx *gfx)
{
	size_t		i;
	t_img		*ptr1;
	t_atlas		*ptr2;

	i = 0;
	ptr1 = (t_img *)&gfx->textures;
	while (i < N_TEXTURES)
	{
		if (ptr1[i].mlx_img)
			mlx_destroy_image(gfx->mlx, ptr1[i].mlx_img);
		ptr1[i++].mlx_img = NULL;
	}
	i = 0;
	ptr2 = gfx->textures.sprites;
	while (ptr2 && i < gfx->texture_files.main_list.len)
	{
		if (ptr2->img.mlx_img)
			mlx_destroy_image(gfx->mlx, ptr2->img.mlx_img);
		(ptr2++)->img.mlx_img = NULL;
		i++;
	}
}

void	unload_textures(t_gfx *gfx)
{
	unload_textures_2(gfx);
	dict_free(&gfx->texture_files);
	free(gfx->textures.size_sprites.arr);
	gfx->textures.size_sprites.arr = NULL;
	free(gfx->textures.sprites);
	gfx->textures.sprites = NULL;
}

static void	deinit_rcs(t_gfx *gfx)
{
	t_render_thread	*cur;
	int				i;

	if (!gfx->render_threads)
		return ;
	i = 0;
	while (i < N_THREADS)
	{
		cur = &gfx->render_threads[i];
		if (cur->rcs)
			free(cur->rcs);
		cur->rcs = NULL;
		i++;
	}
}

void	gfx_unload_scene(t_gfx *gfx)
{
	if (gfx->map.map)
		ft_clean_matrix((void **)gfx->map.map);
	gfx->map.map = NULL;
	unload_textures(gfx);
	if (gfx->map.tile_data)
		ft_clean_matrix((void **)gfx->map.tile_data);
	gfx->map.tile_data = NULL;
	free(gfx->entities.arr);
	gfx->entities.arr = NULL;
	pathfinding_free_resources(&gfx->pf_res);
	deinit_rcs(gfx);
	ft_bzero(&gfx->map, sizeof(t_map));
	ft_bzero(&gfx->input, sizeof(t_input));
	gfx->game_vars.n_coins = 0;
	gfx->game_vars.n_coins_collected = 0;
	gfx->game_vars.n_enemies = 0;
	gfx->game_vars.n_enemies_killed = 0;
}

void	gfx_deinit(t_gfx *gfx)
{
	const t_img	*to_free[] = {&gfx->screen1, &gfx->screen2,
		&gfx->minimap_img, &gfx->stats_img, &gfx->hurt_img};
	int			i;

	gfx_unload_scene(gfx);
	i = -1;
	while ((unsigned int)++i < sizeof(to_free) / sizeof(to_free[0]))
		if (to_free[i]->mlx_img)
			mlx_destroy_image(gfx->mlx, to_free[i]->mlx_img);
	unload_static_textures(gfx);
	dict_free(&gfx->game_vars.adventure.properties);
	str_list_free(&gfx->game_vars.adventure.map_lst);
	if (gfx->win)
		mlx_destroy_window(gfx->mlx, gfx->win);
	if (gfx->mlx)
		mlx_destroy_display(gfx->mlx);
	if (gfx->render_threads)
	{
		set_thread_state(gfx, STATE_STOP);
		pthread_cond_broadcast(&gfx->render_cond);
		join_threads(gfx, N_THREADS);
		free(gfx->render_threads);
	}
	free(gfx->mlx);
}
