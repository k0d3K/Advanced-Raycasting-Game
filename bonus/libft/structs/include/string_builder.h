/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:17:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/06 17:52:40 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_BUILDER_H
# define STRING_BUILDER_H

# include <stdlib.h>

typedef struct s_sb
{
	char	*str;
	size_t	capacity;
	size_t	pos;
}	t_sb;

int		sb_init(t_sb *sb, size_t init_cap);
int		sb_appendn(t_sb *sb, char *str, size_t len);
int		sb_append(t_sb *sb, char *str);
int		sb_addchar(t_sb *sb, char c);
int		sb_addu64(t_sb *sb, unsigned long long n);
int		sb_addi64(t_sb *sb, long long n);
char	*sb_build(t_sb *sb);

#endif