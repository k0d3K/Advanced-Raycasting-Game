/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:02:13 by dath              #+#    #+#             */
/*   Updated: 2025/03/04 00:19:05 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <assert.h>

void	free_list_range(t_generic_list *lst, size_t start, size_t stop)
{
	while (start < stop)
		free(lst->arr[start++]);
}

void	str_list_free(t_str_list *lst)
{
	if (lst->components_are_allocated)
		free_list_range((t_generic_list *)lst, 0, lst->len);
	free(lst->arr);
	lst->arr = NULL;
}

void	generic_list_free(t_generic_list *lst)
{
	if (lst->components_are_allocated)
		free_list_range(lst, 0, lst->len);
	free(lst->arr);
	lst->arr = NULL;
}
