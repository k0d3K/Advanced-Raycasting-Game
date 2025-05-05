/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:48:05 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/10/09 14:43:58 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**do_alloc(const char *str, char c)
{
	int		len;
	char	**ptr;

	len = 1;
	if (*str != '\0')
	{
		len++;
		while (*(str + 1))
		{
			if (*str == c && *(str + 1) != c)
				len++;
			str++;
		}
	}
	ptr = malloc(sizeof(char *) * len);
	return (ptr);
}

static char	**free_strs(char **r, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(r[i++]);
	free(r);
	return (0);
}

static char	**ft_split2(const char *str, char c, char **res)
{
	char	*curr_str;
	int		curr_len;
	int		i;
	int		j;

	i = 0;
	while (*str)
	{
		curr_len = 0;
		while (str[curr_len] && str[curr_len] != c)
			curr_len++;
		curr_str = malloc(sizeof(char) * (curr_len + 1));
		if (!curr_str)
			return (free_strs(res, i));
		res[i++] = curr_str;
		j = -1;
		while (++j < curr_len)
			*curr_str++ = *str++;
		*curr_str = '\0';
		while (*str && *str == c)
			str++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	char	trim_arr[2];
	char	*trimmed;

	trim_arr[0] = c;
	trim_arr[1] = '\0';
	trimmed = ft_strtrim(s, trim_arr);
	if (!trimmed)
		return (0);
	res = do_alloc(trimmed, c);
	if (!res)
	{
		free(trimmed);
		return (0);
	}
	res = ft_split2(trimmed, c, res);
	free(trimmed);
	return (res);
}
