/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:11:17 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/16 10:52:53 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

int	dict_init(t_dict *dict, int components_are_allocated)
{
	if (!uint_list_init(&dict->hash_list, 50))
		return (0);
	if (!str_list_init(&dict->main_list, 50, components_are_allocated))
	{
		free(dict->hash_list.arr);
		return (0);
	}
	return (1);
}

void	dict_free(t_dict *dict)
{
	if (dict->main_list.arr)
		str_list_free(&dict->main_list);
	if (dict->hash_list.arr)
	{
		free(dict->hash_list.arr);
		dict->hash_list.arr = NULL;
	}
}
