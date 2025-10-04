/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:18:01 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/05/06 16:34:06 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDING_H
# define PATHFINDING_H

# include <stdint.h>
# include "utils.h"

// https://web.archive.org/web/20170326190003/
// https://www.policyalmanac.org/games/aStarTutorial.htm

# define H_V_MOVEMENT_COST	10	// horizontal or verical movement G-cost
# define D_MOVEMENT_COST	14	// diagonal movement G-cost
# define JUMP_COST			7	// will be added to the total G-cost of a node
# define DOOR_COST			20	// will be added to the total G-cost of a node

typedef struct s_node	t_node;

typedef struct s_node
{
	t_node			*next;

	t_node			*parent_node;
	t_point			p;
	uint16_t		g_cost;
	uint16_t		h_cost;
	uint16_t		f_cost;
	t_tile			tile;
}	t_node;

typedef struct s_node_pool
{
	t_node		*arr;
	uint32_t	idx;
	uint32_t	capacity;
}	t_node_pool;

int			node_pool_init(t_node_pool *pool, uint32_t capacity);
t_node		*node_pool_fetch(t_node_pool *pool);

typedef struct s_node_list
{
	t_node			*first;
	uint32_t		size;
	t_node_pool		pool;
}	t_node_list;

int			node_list_init(t_node_list *lst, uint32_t max_capacity);
t_node		*node_list_insert(t_node_list *lst, t_node node);
t_node		*node_list_fetch_least_costly_node(t_node_list *lst);
t_node		*node_list_get_node_with_pos(t_node_list *lst, t_point p);
void		node_list_clear(t_node_list *lst);

typedef struct s_entity	t_entity;
typedef struct s_gfx	t_gfx;

typedef struct s_pathfinding_resources
{
	t_node_list	node_list;
	uint8_t		**traversed_nodes;
}	t_pathfinding_resources;

typedef struct s_pathfinding_vars
{
	t_node			*cur_node;
	t_node_list		*open_list;
	uint8_t			**traversed_node_map;
	t_map			*map;
	t_point			end_pos;
	t_node			*end_node;
}	t_pathfinding_vars;

int			pathfinding_init_resources(
				t_pathfinding_resources *res, t_map *map);
void		pathfinding_free_resources(t_pathfinding_resources *res);

int			pf_can_cross_diagonal_node(t_pathfinding_vars *v, t_point p);
void		pf_add_all_adjacent_nodes(t_pathfinding_vars *v);
uint32_t	pf_calculate_h_cost(t_pathfinding_vars *v, t_point p);
void		pf_debug_show_line(
				t_gfx *gfx, t_point start, t_point end);

t_node		*pf_impl(
				t_point start_pos, t_point end_pos, t_gfx *gfx);
void		pathfinding_calc_path(t_gfx *gfx, t_entity *e);

#endif
