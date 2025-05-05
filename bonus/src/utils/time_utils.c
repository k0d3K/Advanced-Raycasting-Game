/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:10:17 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/12 17:13:16 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>

inline uint64_t	get_time_micro(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + tv.tv_sec * SEC_MICRO);
}

void	ft_usleep(uint64_t micro)
{
	uint64_t	beginning;

	beginning = get_time_micro();
	while (get_time_micro() - beginning < micro)
		;
}
