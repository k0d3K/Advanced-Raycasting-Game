/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:03:09 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 00:31:41 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "geo.h"
# include "strings.h"

size_t		size_tab(char **tab);

void		ft_clean_matrix(void **matrix);
void		ft_free_matrix(void **matrix, size_t size);
char		*skip_empty_lines(int fd);
t_cardinal	get_character_orientation(char c);
float		cardinal_to_angle(t_cardinal c);
void		error(char *fmt, ...);

#endif