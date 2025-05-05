/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:03:09 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/18 14:05:56 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "libft.h"
# include "geo.h"
# include "strings.h"
# include "rendering.h"

size_t			size_tab(char **tab);

void			ft_clean_matrix(void **matrix);
void			ft_free_matrix(void **matrix, size_t size);
t_face			get_character_orientation(char c);
float			face_to_angle(t_face c);
void			error(char *fmt, ...);

# define SEC_MICRO	1000000UL

uint64_t		get_time_micro(void);
void			ft_usleep(uint64_t micro);

t_thread_state	get_thread_state(t_gfx *gfx);
void			set_thread_state(t_gfx *gfx, t_thread_state state);
void			wait_until_all_slices_rendered(t_gfx *gfx);
void			join_threads(t_gfx *gfx, int n);

int				get_wall_height(char c);
t_img			*get_face_image(t_face face, t_gfx *gfx);

typedef struct s_compute_cache_params
{
	size_t	start;
	size_t	end;
	size_t	type_size;
	void	(*fn)(void *store, size_t idx);
}	t_compute_cache_params;

typedef struct s_compute_cache
{
	void	*cache;
	size_t	len;
}	t_compute_cache;

int				compute_cache_init(t_compute_cache *out,
					t_compute_cache_params params);

uint32_t		str_crc32(char *str);

typedef struct s_dict
{
	t_uint_list	hash_list;
	t_str_list	main_list;
}	t_dict;

int				dict_init(t_dict *dict, int components_are_allocated);
size_t			dict_indexof(t_dict *dict, char *key);
int				dict_contains_key(t_dict *dict, char *key);
void			dict_free(t_dict *dict);
int				dict_add(t_dict *dict, char *key, char *value);
char			*dict_fetch(t_dict *dict, char *key);
int				dict_remove(t_dict *dict, char *key);

#endif