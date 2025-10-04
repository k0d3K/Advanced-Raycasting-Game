/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:43:46 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/14 17:33:37 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_LIST_H
# define CHAR_LIST_H

# include <stddef.h>

typedef struct s_char_list
{
	char	*arr;
	size_t	cap;
	size_t	len;
}	t_char_list;

# define LIST_INCREMENT	50

int		char_list_init(t_char_list *lst, size_t init_cap);
int		char_list_add(t_char_list *lst, char n);
void	char_list_remove(t_char_list *lst, size_t start, size_t n);
size_t	char_list_indexof(t_char_list *lst, char o);
int		char_list_contains(t_char_list *lst, char o);

#endif
