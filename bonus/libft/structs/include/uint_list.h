/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:43:46 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/08 11:49:37 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UINT_LIST_H
# define UINT_LIST_H

# include <stdint.h>
# include <stddef.h>

typedef struct s_uint_list
{
	uint32_t	*arr;
	size_t		cap;
	size_t		len;
}	t_uint_list;

# define LIST_INCREMENT	50

int		uint_list_init(t_uint_list *lst, size_t init_cap);
int		uint_list_add(t_uint_list *lst, uint32_t n);
void	uint_list_remove(t_uint_list *lst, size_t start, size_t n);
size_t	uint_list_indexof(t_uint_list *lst, uint32_t o);
int		uint_list_contains(t_uint_list *lst, uint32_t o);

#endif
