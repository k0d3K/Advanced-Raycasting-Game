/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_cache.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:23:46 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/26 16:50:19 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "utils.h"

int	compute_cache_init(t_compute_cache *out,
	t_compute_cache_params params)
{
	size_t	i;
	size_t	ptr;
	size_t	len;

	assert(params.start < params.end && out && params.fn);
	len = params.end - params.start;
	out->len = len;
	out->cache = malloc(len * params.type_size);
	if (!out->cache)
		return (0);
	i = params.start;
	ptr = (size_t)out->cache;
	while (i < params.end)
	{
		params.fn((void *)ptr, i);
		ptr += params.type_size;
		i++;
	}
	return (1);
}
