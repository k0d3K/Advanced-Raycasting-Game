/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:43:46 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/04 00:17:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_LIST_H
# define STR_LIST_H

# include <stddef.h>

typedef struct s_str_list
{
	char	**arr;
	size_t	cap;
	size_t	len;
	int		components_are_allocated;
}	t_str_list;

# define LIST_INCREMENT	50

int		str_list_init(t_str_list *lst, size_t init_cap,
			int components_are_allocated);
int		str_list_add(t_str_list *lst, char *n);
void	str_list_remove(t_str_list *lst, size_t start, size_t n);
size_t	str_list_indexof(t_str_list *lst, char *o);
int		str_list_contains(t_str_list *lst, char *o);
void	str_list_free(t_str_list *lst);

#endif
