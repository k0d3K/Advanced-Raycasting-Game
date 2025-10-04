/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:44:13 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/29 19:26:56 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static inline __attribute__((always_inline))
	void	__put(t_img img, t_point p, t_color c)
{
	int		offset;
	t_color	*addr;

	offset = p.y * img.size.x + p.x;
	addr = img.data + offset;
	*addr = c;
}

static inline __attribute__((always_inline))
	void	set_defaults(t_bresenham *b)
{
	b->dir.p = b->to.p - b->from.p;
	b->dir.x = (b->dir.x > 0) * b->dir.x - (b->dir.x < 0) * b->dir.x;
	b->dir.y = (b->dir.y > 0) * -b->dir.y + (b->dir.y < 0) * b->dir.y;
	b->sign.x = -1 + (b->to.x > b->from.x) * 2;
	b->sign.y = -1 + (b->to.y > b->from.y) * 2;
	b->err = b->dir.x + b->dir.y;
}

static inline __attribute__((always_inline))
	int	gfx_skip_oob(t_bresenham *b)
{
	while (b->to.x < 0 || b->to.x >= WIN_W
		|| b->to.y < 0 || b->to.y >= WIN_H)
	{
		if (b->from.x == b->to.x && b->from.y == b->to.y)
			return (0);
		b->e2 = 2 * b->err;
		b->err += b->dir.y * (b->e2 >= b->dir.y);
		b->to.x -= b->sign.x * (b->e2 >= b->dir.y);
		b->err += b->dir.x * (b->e2 <= b->dir.x);
		b->to.y -= b->sign.y * (b->e2 <= b->dir.x);
	}
	b->err = b->dir.x + b->dir.y;
	while (b->from.x < 0 || b->from.x >= WIN_W
		|| b->from.y < 0 || b->from.y >= WIN_H)
	{
		if (b->from.x == b->to.x && b->from.y == b->to.y)
			return (0);
		b->e2 = 2 * b->err;
		b->err += b->dir.y * (b->e2 >= b->dir.y);
		b->from.x += b->sign.x * (b->e2 >= b->dir.y);
		b->err += b->dir.x * (b->e2 <= b->dir.x);
		b->from.y += b->sign.y * (b->e2 <= b->dir.x);
	}
	return (1);
}

void	gfx_line(t_gfx *gfx, t_point from, t_point to, t_color c)
{
	t_bresenham	b;

	b.from = from;
	b.to = to;
	set_defaults(&b);
	if (!gfx_skip_oob(&b))
		return ;
	set_defaults(&b);
	while (1)
	{
		__put(*gfx->screen, b.from, c);
		if (b.from.x == b.to.x && b.from.y == b.to.y)
			break ;
		b.e2 = 2 * b.err;
		b.err += b.dir.y * (b.e2 >= b.dir.y);
		b.from.x += b.sign.x * (b.e2 >= b.dir.y);
		b.err += b.dir.x * (b.e2 <= b.dir.x);
		b.from.y += b.sign.y * (b.e2 <= b.dir.x);
	}
}
