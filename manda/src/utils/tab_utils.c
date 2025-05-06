/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:27:31 by lguerbig          #+#    #+#             */
/*   Updated: 2025/05/06 16:02:58 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Get the size of a tab
 * 
 * @param tab The tab
 * 
 * @return The size of the tab
 */
size_t	size_tab(char **tab)
{
	size_t	size;

	if (!tab)
		return (0);
	size = 0;
	while (tab[size])
		size++;
	return (size);
}

/**
 * @brief Free a matrix
 * 
 * @param matrix The matrix to free
 */
void	ft_clean_matrix(void **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		++i;
	}
	free(matrix);
}
