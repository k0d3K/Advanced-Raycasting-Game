/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:43:46 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/04 00:22:19 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_LIST_H
# define GENERIC_LIST_H

# include <stddef.h>

typedef struct s_generic_list
{
	void	**arr;
	size_t	cap;
	size_t	len;
	int		components_are_allocated;
}	t_generic_list;

# define LIST_INCREMENT	50

int		generic_list_init(t_generic_list *lst, size_t init_cap,
			int components_are_allocated);
int		generic_list_add(t_generic_list *lst, void *n);
void	generic_list_remove(t_generic_list *lst, size_t start, size_t n);
size_t	generic_list_indexof(t_generic_list *lst, void *o);
int		generic_list_contains(t_generic_list *lst, void *o);
void	generic_list_free(t_generic_list *lst);

void	free_list_range(t_generic_list *lst, size_t start, size_t stop);

#endif
