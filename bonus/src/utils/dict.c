/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:41:55 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/10 11:20:39 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <assert.h>

size_t	dict_indexof(t_dict *dict, char *key)
{
	uint32_t	crc;
	uint32_t	*arr;
	size_t		i;
	size_t		len;

	crc = str_crc32(key);
	assert(dict->hash_list.arr);
	arr = dict->hash_list.arr;
	i = 0;
	len = dict->hash_list.len;
	while (i < len)
	{
		if (arr[i] == crc)
			return (i);
		i++;
	}
	return ((size_t)-1);
}

int	dict_contains_key(t_dict *dict, char *key)
{
	return (dict_indexof(dict, key) != (size_t)-1);
}

int	dict_add(t_dict *dict, char *key, char *value)
{
	uint32_t	crc;

	if (!dict->hash_list.arr)
		return (0);
	if (dict_indexof(dict, key) != (size_t)-1)
		return (1);
	crc = str_crc32(key);
	if (!uint_list_add(&dict->hash_list, crc))
	{
		dict_free(dict);
		return (0);
	}
	if (!str_list_add(&dict->main_list, value))
	{
		dict_free(dict);
		return (0);
	}
	return (1);
}

char	*dict_fetch(t_dict *dict, char *key)
{
	size_t		idx;

	assert(dict->hash_list.arr);
	idx = dict_indexof(dict, key);
	if (idx == (size_t)-1)
		return (NULL);
	return (dict->main_list.arr[idx]);
}

int	dict_remove(t_dict *dict, char *key)
{
	size_t		idx;

	assert(dict->hash_list.arr);
	idx = dict_indexof(dict, key);
	if (idx == (size_t)-1)
		return (0);
	uint_list_remove(&dict->hash_list, idx, 1);
	str_list_remove(&dict->main_list, idx, 1);
	return (1);
}
