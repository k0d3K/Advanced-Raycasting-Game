/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:23 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/02/07 15:43:04 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2000
#endif

static char	*eol_pos(char *buf, int max)
{
	int	i;

	i = 0;
	while (i < max && *buf && *buf != '\n')
	{
		buf++;
		i++;
	}
	if (i == max || *buf != '\n')
		return (0);
	return (buf + 1);
}

static int	read_with_buf(int fd, char *dest_buf, char *gnl_buf, int *buf_read)
{
	char	*eol;
	int		n_read;

	n_read = 0;
	eol = eol_pos(gnl_buf, BUFFER_SIZE);
	if (eol)
	{
		*buf_read += eol - gnl_buf;
		ft_memcpy(dest_buf, gnl_buf, *buf_read);
		ft_memcpy(gnl_buf, eol, BUFFER_SIZE - *buf_read);
		gnl_buf[BUFFER_SIZE - *buf_read] = '\0';
	}
	else
	{
		if (!*buf_read)
		{
			*buf_read += ft_strlcpy(dest_buf, gnl_buf, BUFFER_SIZE);
			ft_bzero(gnl_buf, BUFFER_SIZE);
		}
		n_read = read(fd, dest_buf + *buf_read, BUFFER_SIZE);
		*buf_read += n_read;
	}
	return (n_read);
}

static char	*resize_or_end_buf(
	char *gnl_buf, char *dest_buf, int *dest_buf_size, char *eol)
{
	if (eol)
	{
		if (!*gnl_buf)
			ft_strlcpy(gnl_buf, eol, BUFFER_SIZE);
		dest_buf[eol - dest_buf] = '\0';
	}
	else
	{
		dest_buf = ft_realloc(dest_buf, *dest_buf_size, BUFFER_SIZE);
		if (!dest_buf)
			return (0);
		*dest_buf_size += BUFFER_SIZE;
	}
	return (dest_buf);
}

static char	*gnl(int fd, char *gnl_buf, int dest_buf_size, int *eof_reached)
{
	char	*dest_buf;
	int		n_read;
	char	*eol;
	int		pos;

	dest_buf = ft_calloc(dest_buf_size, sizeof(char));
	if (!dest_buf)
		return (0);
	pos = 0;
	while (1)
	{
		n_read = read_with_buf(fd, dest_buf, gnl_buf, &pos);
		eol = eol_pos(dest_buf, dest_buf_size);
		if (n_read < 0 || (n_read == 0 && !eol))
			break ;
		dest_buf = resize_or_end_buf(gnl_buf, dest_buf, &dest_buf_size, eol);
		if (!dest_buf || eol)
			return (dest_buf);
	}
	*eof_reached = 1;
	if (!eol && !n_read && pos)
		return (dest_buf);
	free(dest_buf);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	gnl_buf[BUFFER_SIZE] = {0};
	char		*dest_buf;
	int			eof_reached;

	eof_reached = 0;
	dest_buf = gnl(fd, gnl_buf, BUFFER_SIZE * 2, &eof_reached);
	if (eof_reached)
		ft_bzero(gnl_buf, BUFFER_SIZE);
	return (dest_buf);
}
