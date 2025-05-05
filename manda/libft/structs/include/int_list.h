/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:43:46 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/14 17:35:53 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_LIST_H
# define INT_LIST_H

# include <stddef.h>

typedef struct s_int_list
{
	int		*arr;
	size_t	cap;
	size_t	len;
}	t_int_list;

# define LIST_INCREMENT	50

int		int_list_init(t_int_list *lst, size_t init_cap);
int		int_list_add(t_int_list *lst, int n);
void	int_list_remove(t_int_list *lst, size_t start, size_t n);
size_t	int_list_indexof(t_int_list *lst, int o);
int		int_list_contains(t_int_list *lst, int o);

#endif
