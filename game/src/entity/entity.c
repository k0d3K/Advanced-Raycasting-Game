/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:31:33 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/19 14:15:52 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"

t_entity	*entity_add(t_gfx *gfx, t_entity e)
{
	if (!entity_list_add(&gfx->entities, e))
		return (NULL);
	return (&gfx->entities.arr[gfx->entities.len - 1]);
}

static __always_inline
	void	swap_entitites(t_entity *a, t_entity *b)
{
	t_entity	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	partition(t_entity *entities, int64_t low, int64_t high)
{
	t_entity	p;
	int64_t		i;
	int64_t		j;

	j = high;
	i = low;
	p = entities[low];
	while (i < j)
	{
		while (entities[i].dist_to_player <= p.dist_to_player && i <= high - 1)
			i++;
		while (entities[j].dist_to_player > p.dist_to_player && j >= low + 1)
			j--;
		if (i < j)
			swap_entitites(&entities[i], &entities[j]);
	}
	swap_entitites(&entities[low], &entities[j]);
	return (j);
}

static void	qsort_rec(t_entity *entities, int64_t low, int64_t high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(entities, low, high);
		qsort_rec(entities, low, pivot - 1);
		qsort_rec(entities, pivot + 1, high);
	}
}

void	sort_entities_by_dist(t_gfx *gfx, t_vec2 pos)
{
	size_t			i;
	t_entity_list	lst;
	t_entity		*e;
	int				force_pathfinding;

	lst = gfx->entities;
	if (!lst.len)
		return ;
	force_pathfinding = gfx->player.need_to_refresh_pathfinding;
	i = 0;
	while (i < lst.len)
	{
		e = &lst.arr[i];
		e->player_dist = (t_vec2)(pos.v - e->plane_pos.v);
		if (!e->player_dist.x && !e->player_dist.y)
			e->dist_to_player = 0;
		else
			e->dist_to_player = vec2_length(e->player_dist);
		entity_check_if_pathfinding_should_be_refreshed(e);
		if (force_pathfinding)
			e->need_to_refresh_pathfinding = 1;
		i++;
	}
	gfx->player.need_to_refresh_pathfinding = 0;
	qsort_rec(lst.arr, 0, lst.len - 1);
}
