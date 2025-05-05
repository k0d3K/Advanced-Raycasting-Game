/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:27:31 by lguerbig          #+#    #+#             */
/*   Updated: 2025/03/08 17:29:40 by lguerbig         ###   ########.fr       */
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
 * @param size The size of the matrix
 */
void	ft_free_matrix(void **matrix, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		++i;
	}
	free(matrix);
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
